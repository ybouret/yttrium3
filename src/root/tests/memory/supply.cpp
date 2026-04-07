#include "y/concurrent/nucleus.hpp"
#include "y/object/light.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/utest/run.hpp"

namespace Yttrium
{

    namespace Memory
    {

        class Supply
        {
        protected:
            explicit Supply(const size_t userBlockSize);

        public:
            virtual ~Supply() noexcept;

            virtual void * zacquire() = 0;
            virtual void   zrelease(void * const) noexcept = 0;

        protected:
            LightObject::Factory &factory;
            void * const          lofNode;

            void * acquireBlock();
            void   releaseBlock(void * const) noexcept;

        public:
            const size_t          blockSize;

        private:
            Y_Disable_Copy_And_Assign(Supply);
        };




    }

}

#include "y/object/light/factory.hpp"

namespace Yttrium
{

    namespace Memory
    {

        Supply:: Supply(const size_t userBlockSize) :
        factory(LightObject::Factory::Instance()),
        lofNode( factory[userBlockSize] ),
        blockSize( static_cast<LightObject::Factory::Node*>(lofNode)->blockSize )
        {
            assert(blockSize==userBlockSize);
        }


        Supply:: ~Supply() noexcept
        {
        }

        void * Supply:: acquireBlock()
        {
            assert(lofNode);
            Y_Lock(factory.access);
            return static_cast<LightObject::Factory::Node*>(lofNode)->acquireBlock();
        }

        void Supply:: releaseBlock(void * const blockAddr) noexcept
        {
            assert(lofNode);
            Y_Lock(factory.access);
            return static_cast<LightObject::Factory::Node*>(lofNode)->releaseBlock(blockAddr);
        }


    }

}



namespace Yttrium
{

    namespace Memory
    {
        
        class DirectSupply : public Supply
        {
        public:
            explicit DirectSupply(const size_t userBlockSize);
            virtual ~DirectSupply() noexcept;

            virtual void * zacquire();
            virtual void   zrelease(void * const) noexcept;

        private:
            Y_Disable_Copy_And_Assign(DirectSupply);

        };

        DirectSupply:: DirectSupply(const size_t userBlockSize) :
        Supply(userBlockSize)
        {
        }

        DirectSupply:: ~DirectSupply() noexcept
        {

        }

        void * DirectSupply:: zacquire()
        {
            return acquireBlock();
        }

        void DirectSupply:: zrelease(void * const blockAddr) noexcept
        {
            releaseBlock(blockAddr);
        }


    }

}


#include "y/core/pool.hpp"
#include "y/ability/caching.hpp"

namespace Yttrium
{

    namespace Memory
    {

        class PooledSupply : public Supply, public Caching
        {
        public:
            explicit PooledSupply(const size_t userBlockSize);
            virtual ~PooledSupply() noexcept;

            virtual void * zacquire();
            virtual void   zrelease(void * const) noexcept;

            virtual void   release() noexcept;
            virtual void   cache(const size_t);
            virtual size_t count() const noexcept;
            virtual void   gc(const uint8_t) noexcept;

        private:
            Y_Disable_Copy_And_Assign(PooledSupply);
            Core::PoolOf<Page> pool;
            void               release_() noexcept;
        };

    }

}

#include <cstring>
#include "y/core/list/to-pool.hpp"
#include "y/core/pool/to-list.hpp"
#include "y/object/light/factory.hpp"

namespace Yttrium
{

    namespace Memory
    {
        PooledSupply:: PooledSupply(const size_t userBlockSize) :
        Supply( Max(sizeof(Page),userBlockSize) ),
        pool()
        {

        }

        PooledSupply:: ~PooledSupply() noexcept
        {
            release_();
        }


        void PooledSupply:: release() noexcept
        {
            release_();
        }

        void PooledSupply:: release_() noexcept
        {
            while(pool.size) releaseBlock( pool.query() );
        }

        void * PooledSupply:: zacquire()
        {
            if(pool.size>0)
                return memset( pool.query(), 0, blockSize);
            else
            {
                return acquireBlock();
            }
        }

        void PooledSupply:: zrelease(void * const blockAddr) noexcept
        {
            assert(0!=blockAddr);
            pool.store( Page::From(blockAddr) );
        }

        size_t PooledSupply:: count() const noexcept
        {
            return pool.size;
        }

        void PooledSupply:: cache(const size_t n)
        {
            LightObject::Factory::Node * const node = static_cast<LightObject::Factory::Node *>(lofNode);
            Y_Lock(factory.access);
            for(size_t i=0;i<n;++i) pool.store( (Page *) node->acquireBlock()  );
        }

        void PooledSupply:: gc(const uint8_t amount) noexcept
        {
            Core::ListOf<Page> list;
            Core::PoolToList::Make(list,pool).sortByDecreasingAddress();
            {
                const size_t newSize = NewSize(amount,list.size);
                LightObject::Factory::Node * const node = static_cast<LightObject::Factory::Node *>(lofNode);
                Y_Lock(factory.access);
                while(list.size>newSize) node->releaseBlock( list.popHead() );
            }
            Core::ListToPool::Make(pool,list);
        }

    }

}

#include "y/ability/auto-locking.hpp"

namespace Yttrium
{
    namespace Memory
    {

        template <typename SUPPLY, typename THREADING_POLICY>
        class LockableSupply : public SUPPLY, public THREADING_POLICY
        {
        public:
            explicit LockableSupply(const size_t bs) :
            SUPPLY(bs),
            THREADING_POLICY()
            {
            }

            virtual ~LockableSupply() noexcept
            {
            }


        private:
            Y_Disable_Copy_And_Assign(LockableSupply);
        };

        template <typename SUPPLY, typename THREADING_POLICY>
        class StorageBase
        {
        public:
            typedef LockableSupply<SUPPLY,THREADING_POLICY> SupplyType;

            inline explicit StorageBase(const size_t bs) : supply(bs) {}
            inline virtual ~StorageBase() noexcept {}

        protected:
            SupplyType supply;

        private:
            Y_Disable_Copy_And_Assign(StorageBase);
        };


        template <typename SUPPLY, typename THREADING_POLICY>
        class Storage :
        public StorageBase<SUPPLY,THREADING_POLICY>,
        public AutoLocking< typename StorageBase<SUPPLY,THREADING_POLICY>::SupplyType >
        {
        public:
            typedef StorageBase<SUPPLY,THREADING_POLICY> StorageType;
            typedef typename StorageType::SupplyType     SupplyType;
            using StorageType::supply;

            inline explicit Storage(const size_t bs) :
            StorageType(bs),
            AutoLocking<SupplyType>(supply)
            {
            }


            inline virtual ~Storage() noexcept
            {
            }

        private:
            Y_Disable_Copy_And_Assign(Storage);
        };


    }

}


#include "y/threading/single-threaded-class.hpp"

using namespace Yttrium;

Y_UTEST(memory_supply)
{
    
    Memory::DirectSupply ds(18);
    Memory::PooledSupply ps(18);

    Y_SIZEOF(Memory::DirectSupply);
    Y_SIZEOF(Memory::PooledSupply);

    Memory::Storage<Memory::DirectSupply,SingleThreadedClass> ds_stc(18);


    void * blockAddr = ds_stc->zacquire();
    ds_stc->zrelease(blockAddr);

}
Y_UDONE()



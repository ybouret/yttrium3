#include "y/concurrent/nucleus.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/utest/run.hpp"

namespace Yttrium
{

    namespace Memory
    {

        class Supply
        {
        protected:
            explicit Supply(const size_t dataBlockSize);
        public:
            virtual ~Supply() noexcept;

            virtual void * summon() = 0;
            virtual void   banish(void * const) noexcept = 0;

        protected:
            Small::Arena &arena;

        private:
            Y_Disable_Copy_And_Assign(Supply);
        };

        namespace {
            static inline Small::Arena & SupplyGet(const size_t blockSize)
            {
                static Small::Blocks &blocks = *Concurrent::Nucleus::Instance().blocks;
                return blocks[blockSize];
            }
        }

    }

}


namespace Yttrium
{

    namespace Memory
    {
        Supply:: Supply(const size_t dataBlockSize) :
        arena( SupplyGet(dataBlockSize) )
        {

        }

        Supply:: ~Supply() noexcept
        {
        }



        class DirectSupply : public Supply
        {
        public:
            explicit DirectSupply(const size_t userBlockSize);
            virtual ~DirectSupply() noexcept;

            virtual void * summon();
            virtual void   banish(void * const) noexcept;

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

        void * DirectSupply:: summon()
        {
            return arena.acquire();
        }

        void DirectSupply:: banish(void * const blockAddr) noexcept
        {
            arena.release(blockAddr);
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
            explicit PooledSupply(const size_t userBlockSize,
                                  Lockable    &userLock);
            virtual ~PooledSupply() noexcept;

            virtual void * summon();
            virtual void   banish(void * const) noexcept;
            
            virtual void   release() noexcept;
            virtual void   cache(const size_t);
            virtual void   gc(const uint8_t) noexcept;

            Lockable          &access;
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

namespace Yttrium
{

    namespace Memory
    {
        PooledSupply:: PooledSupply(const size_t userBlockSize,
                                    Lockable &   userLock) :
        Supply( Max(sizeof(Page),userBlockSize) ),
        access(userLock),
        pool()
        {

        }

        PooledSupply:: ~PooledSupply() noexcept
        {
            release_();
        }


        void PooledSupply:: release() noexcept
        {
            Y_Lock(access);
            release_();
        }

        void PooledSupply:: release_() noexcept
        {
            while(pool.size) arena.release(pool.query());
        }

        void * PooledSupply:: summon()
        {
            Y_Lock(access);
            if(pool.size>0)
                return memset( pool.query(), 0, arena.blockSize);
            else
                return arena.acquire();
        }

        void PooledSupply:: banish(void * const blockAddr) noexcept
        {
            assert(0!=blockAddr);
            Y_Lock(access);
            pool.store( Page::From(blockAddr) );
        }

        void PooledSupply:: cache(const size_t n)
        {
            Y_Lock(access);
            Y_Lock(arena.access);
            for(size_t i=0;i<n;++i) pool.store( static_cast<Page *>(arena.acquire()) );
        }

        void PooledSupply:: gc(const uint8_t amount) noexcept
        {
            Y_Lock(access);
            Core::ListOf<Page> list;
            {
                Core::PoolToList::Make(list,pool).sortByDecreasingAddress();
                const size_t newSize = NewSize(amount,list.size);
                Y_Lock(arena.access);
                while(list.size>newSize)
                    arena.release( list.popHead() );
            }
            Core::ListToPool::Make(pool,list);
        }

    }

}


using namespace Yttrium;

Y_UTEST(memory_supply)
{

}
Y_UDONE()



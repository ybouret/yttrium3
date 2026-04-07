#include "y/concurrent/nucleus.hpp"
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
            explicit Supply(const size_t dataBlockSize);
        public:
            virtual ~Supply() noexcept;

            virtual void * zacquire() = 0;
            virtual void   zrelease(void * const) noexcept = 0;

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
            return arena.acquire();
        }

        void DirectSupply:: zrelease(void * const blockAddr) noexcept
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

            virtual void * zacquire();
            virtual void   zrelease(void * const) noexcept;

            virtual void   release() noexcept;
            virtual void   cache(const size_t);
            virtual size_t count() const noexcept;
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

        void * PooledSupply:: zacquire()
        {
            Y_Lock(access);
            if(pool.size>0)
                return memset( pool.query(), 0, arena.blockSize);
            else
                return arena.acquire();
        }

        void PooledSupply:: zrelease(void * const blockAddr) noexcept
        {
            assert(0!=blockAddr);
            Y_Lock(access);
            pool.store( Page::From(blockAddr) );
        }

        size_t PooledSupply:: count() const noexcept
        {
            return pool.size;
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

namespace Yttrium
{
    namespace Memory
    {

#define Y_Memory_Zombies(CODE) do {\
/**/    void * const addr = this->zacquire();\
/**/    try { CODE;  }\
/**/    catch(...) { this->zrelease(addr); throw; } \
/**/    } while(false)

        template <typename T, typename SUPPLY>
        class Zombies : public SUPPLY
        {
        public:
            Y_Args_Expose(T,Type);
            typedef SUPPLY SupplyType;

            inline explicit Zombies() : SupplyType(sizeof(T))
            {

            }

            inline explicit Zombies(Lockable &userLock) : SupplyType(sizeof(T),userLock)
            {

            }


            inline virtual ~Zombies() noexcept
            {
            }


            inline Type * summon()
            {
                Y_Memory_Zombies( return new (addr) MutableType()  );
            }

            template <typename U>
            inline Type * summon(U &u)
            {
                Y_Memory_Zombies( return new (addr) MutableType(u)  );
            }

            template <typename U, typename V>
            inline Type * summon(U &u, V& v)
            {
                Y_Memory_Zombies( return new (addr) MutableType(u,v)  );
            }

            inline Type * mirror(ConstType &other)
            {
                Y_Memory_Zombies( return new (addr) MutableType(other)  );
            }

            inline void banish(Type * const alive) noexcept
            {
                this->zrelease( Destructed( (MutableType*)alive ) );
            }

        private:
            Y_Disable_Copy_And_Assign(Zombies);
        };
    }
}

using namespace Yttrium;

Y_UTEST(memory_supply)
{

    Concurrent::Mutex    mutex;
    Memory::DirectSupply ds(10);
    Memory::PooledSupply ps(10,mutex);

}
Y_UDONE()



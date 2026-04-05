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

namespace Yttrium
{

    namespace Memory
    {


    }

}


using namespace Yttrium;

Y_UTEST(memory_supply)
{

}
Y_UDONE()



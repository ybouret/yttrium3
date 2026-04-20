#include "y/memory/troop.hpp"
#include "y/object/factory.hpp"

namespace Yttrium
{
    namespace Memory
    {

        TroopGear:: TroopGear() noexcept
        {
        }

        TroopGear:: ~TroopGear() noexcept
        {
        }

        void  * TroopGear:: Acquire(size_t &count, size_t &bytes, const size_t bytesPerItem)
        {
            assert(bytesPerItem>0);
            assert(0==bytes);

            if(count>0)
            {
                static Memory::Allocator & mgr = Object::Factory::Instance();
                bytes = count * bytesPerItem;
                try {
                    void * const blockAddr = mgr.acquire(bytes);
                    count = bytes / bytesPerItem;
                    return blockAddr;
                }
                catch(...)
                {
                    assert(0==bytes);
                    count = 0;
                    throw;
                }
            }
            else
            {
                return 0;
            }
        }

        void TroopGear:: Release(void * addr, size_t &count, size_t &bytes) noexcept
        {
            if(addr)
            {
                static Memory::Allocator & mgr = Object::Factory::Location();
                mgr.release(addr,bytes); assert(0==bytes);
                count = 0;
            }
            else
            {
                assert(0==count);
                assert(0==bytes);
            }
        }
    }

}




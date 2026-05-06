#include "y/core/htable.hpp"
#include "y/exception.hpp"
#include "y/core/max.hpp"
#include "y/object.hpp"
#include "y/calculus/prime/prev.hpp"
#include "y/type/destroy.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/libc/block/zeroed.h"
#include <iostream>
#include "y/pointer/auto.hpp"

namespace Yttrium
{

    namespace Core
    {
        const char * const HTable:: CallSign = "Core::HTable";

        class HTable:: Code : public Object
        {
        public:
            static const size_t _1 = 1;

            inline explicit Code(const size_t minCapacity) :
            size(0),
            capacity(minCapacity),
            slotNum( SlotsFor( Coerce(capacity)) ),
            slotMsk(slotNum-1),
            slotSub( Prime::Prev(slotNum) ),
            myShift( ExactLog2(slotNum) + ShiftPerSlot ),
            slots( Acquire(myShift) ),
            myBytes( _1 << myShift )
            {
                std::cerr << "capacity = " << capacity << std::endl;
                std::cerr << "slotNum  = " << slotNum  << std::endl;
                std::cerr << "slotSub  = " << slotSub  << std::endl;
                assert( Y_TRUE == Yttrium_Zeroed(slots,myBytes) );
            }

            inline virtual ~Code() noexcept
            {
                static Memory::Archon & archon = Memory::Archon::Location();
                archon.releaseBlock(slots,myShift);
            }

            const size_t   size;
            const size_t   capacity;
            const size_t   slotNum;
            const size_t   slotMsk;
            const size_t   slotSub;
            const unsigned myShift;
            Slot * const   slots;
            const size_t   myBytes;

            inline const void * search(const size_t key) const noexcept
            {
                size_t idx = (key & slotMsk); // starting index
                size_t met = 0;               // met items
                for(size_t i=slotNum;i>0;--i, (idx += slotSub) &= slotMsk )
                {
                    if(met>=size) return 0;
                    const Slot * const slot = &slots[idx];
                    const void *       args = slot->args;
                    if(!args) continue;
                    ++met;
                    if(key==slot->key) return args;
                }
                return 0;
            }





            inline bool insert(const size_t key, void * const args)
            {
                assert(size<capacity);
                assert(args!=0);

                size_t idx = (key & slotMsk); // starting index
                for(size_t i=slotNum;i>0;--i, (idx += slotSub) &= slotMsk )
                {
                    Slot * const slot = &slots[idx];
                    if(slot->args)
                    {
                        if(key == slot->key) return false;
                        continue;
                    }
                    slot->key  = key;
                    slot->args = args;
                    ++Coerce(size);
                    return true;
                }
                throw Specific::Exception(CallSign, "unexpected insert look up failure");
            }

            inline void steal(Code &code)
            {
                assert(0==size);
                assert(capacity>=code.size);

                try
                {
                    // scan code
                    size_t met = 0;
                    for(size_t i=0;i<code.slotNum;++i)
                    {
                        if(met>=code.size) break;
                        Slot & source = code.slots[i];
                        if(!source.args) continue;
                        ++met;
                        if(!insert(source.key,source.args))
                            throw Specific::Exception(CallSign,"unexpected steal failure");
                    }

                    // clean code
                    assert(size==code.size);
                    Coerce(code.size) = 0;
                    Yttrium_BZero(code.slots,code.myBytes);
                }
                catch(...)
                {
                    Coerce(size)=0;
                    throw;
                }


            }



        private:
            Y_Disable_Copy_And_Assign(Code);

            static inline Slot * Acquire(const unsigned blockShift)
            {
                static Memory::Archon & archon = Memory::Archon::Instance();
                return static_cast<Slot *>(archon.acquireBlock(blockShift));
            }
        };

        HTable:: HTable(const size_t minCapacity) : code( new Code(minCapacity) )
        {
        }

        HTable:: ~HTable() noexcept
        {
            Destroy(code);
        }


        size_t HTable:: SlotsFor(size_t &minCapacity)
        {
            if(minCapacity>MaxTableSize) throw Specific::Exception(CallSign, "size overflow");
            InSituMax(minCapacity,MinTableSize);
            size_t numSlots = MaxLoadDenom * (minCapacity/MaxLoadNumer);
            numSlots        = NextPowerOfTwo(numSlots);
            minCapacity     = MaxLoadNumer * (numSlots/MaxLoadDenom);
            return numSlots;
        }

        size_t HTable:: size()     const noexcept { assert(code); return code->size;     }
        size_t HTable:: capacity() const noexcept { assert(code); return code->capacity; }


        const void * HTable:: search(const size_t key) const noexcept
        {
            assert(code);
            return code->search(key);
        }

        void * HTable:: search(const size_t key) noexcept
        {
            assert(code);
            return (void*)(code->search(key));
        }

        void HTable:: reserve(const size_t n)
        {
            assert(code);
            if(n<=0) return;
            AutoPtr<Code> tmp = new Code(code->capacity+n);
            tmp->steal(*code);
            delete code;
            Coerce(code) = tmp.yield();
        }

        bool HTable:: insert(const size_t key, void * const args)
        {
            if(code->size<code->capacity)
            {
                return code->insert(key,args);
            }
            else
            {
                std::cerr << "Not Implemented" << std::endl;
                return false;
            }
        }


    }

}

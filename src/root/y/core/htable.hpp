
//! \file

#ifndef Y_Core_HTable_Included
#define Y_Core_HTable_Included 1

#include "y/calculus/base2.hpp"
#include "y/calculus/integer-log2.hpp"
#include "y/config/setup.hpp"
#include "y/container.hpp"
#include "y/ability/expandable.hpp"

namespace Yttrium
{

    namespace Core
    {

        class HTable : public Expandable<Container>
        {
        public:
            static const char * const CallSign; //!< "Core::HTable"
            struct Slot {
                size_t key;
                void * args;
            };

            static const size_t ShiftPerSlot = IntegerLog2For<Slot>::Value;
            static const size_t MaxLoadNumer = 3;
            static const size_t MaxLoadDenom = 4;
            static const size_t BytesPerSlot = sizeof(Slot);
            static const size_t MaxPageBytes = Base2<size_t>::MaxBytes;
            static const size_t MaxSlotCount = MaxPageBytes / BytesPerSlot;
            static const size_t MinSlotCount = 4;
            static const size_t MinTableSize = MaxLoadNumer * (MinSlotCount/MaxLoadDenom);
            static const size_t MaxTableSize = MaxLoadNumer * (MaxSlotCount/MaxLoadDenom);
            static size_t SlotsFor(size_t &minCapacity);


            explicit HTable(const size_t minCapacity = 0);
            virtual ~HTable() noexcept;

            virtual size_t size()     const noexcept;
            virtual size_t capacity() const noexcept;

            const void * search(const size_t key) const noexcept;
            void *       search(const size_t key) noexcept;
            bool         remove(const size_t key) noexcept;
            

            bool insert(const size_t key, void * const args);
            void reserve(const size_t n);

        private:
            Y_Disable_Copy_And_Assign(HTable);
            class Code;
            Code * const code;
        };

    }

}

#endif // !Y_Core_HTable_Included

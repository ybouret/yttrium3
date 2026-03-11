
//! \file

#ifndef Y_Memory_ExternC_Included
#define Y_Memory_ExternC_Included 1


#include "y/type/args.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/bzero.h"

namespace Yttrium
{

    namespace Memory
    {

        template <typename T>
        class ExternC
        {
        public:
            Y_Args_Expose(T,Type);

            inline explicit ExternC() noexcept : addr(0), wksp()
            {
                Coerce(addr) = static_cast<MutableType *>( Y_BZero(wksp) );
            }

            inline virtual ~ExternC() noexcept
            {
                Y_BZero(wksp);
            }

            MutableType * operator()(void)       noexcept { return addr; }
            ConstType   * operator()(void) const noexcept { return addr; }
            
        private:
            Y_Disable_Copy_And_Assign(ExternC);
            MutableType * const addr;
            void * wksp[ Alignment::WordsFor<T>::Count ];
        };
    }

}

#endif // !Y_Memory_ExternC_Included


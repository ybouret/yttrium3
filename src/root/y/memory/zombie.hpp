
//! \file

#ifndef Y_Memory_Zombie_Included
#define Y_Memory_Zombie_Included 1


#include "y/type/args.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/bzero.h"

namespace Yttrium
{

    namespace Memory
    {

        template <typename T, const size_t N=1>
        class Zombie
        {
        public:
            Y_Args_Expose(T,Type);
            static const size_t size = N;
            
            inline explicit Zombie() noexcept : ptr(0), cxx(0), wksp()
            {
                Coerce(ptr) = static_cast<MutableType *>( Y_BZero(wksp) );
                Coerce(cxx) = ptr-1;
            }

            inline virtual ~Zombie() noexcept
            {
                Y_BZero(wksp);
            }

            inline Type & operator[](const size_t indx) noexcept
            {
                assert(indx>=1); assert(indx<=size); return cxx[indx];
            }

            inline ConstType & operator[](const size_t indx) const noexcept
            {
                assert(indx>=1); assert(indx<=size); return cxx[indx];
            }

            inline MutableType * operator()(void)       noexcept { return ptr; }
            inline ConstType   * operator()(void) const noexcept { return ptr; }

        private:
            Y_Disable_Copy_And_Assign(Zombie);
            MutableType * const ptr;
            MutableType * const cxx;
            void * wksp[ Alignment::WordsGEQ<sizeof(T)*N>::Count ];
        };
    }

}

#endif // !Y_Memory_Zombie_Included


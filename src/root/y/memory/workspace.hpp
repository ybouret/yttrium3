

//! \file

#ifndef Y_Memory_Workspace_Included
#define Y_Memory_Workspace_Included 1

#include "y/calculus/alignment.hpp"
#include "y/config/setup.hpp"
#include "y/libc/bzero.h"

namespace Yttrium
{
    namespace Memory
    {
        template <typename T,const size_t N>
        class Workspace
        {
        public:
            static const size_t Size = N;

            inline  Workspace() noexcept :
            cxx(0), wksp()
            {
                Coerce(cxx) = static_cast<T *>( Y_BZero(wksp) )-1;
            }

            T & operator[](const size_t indx) noexcept
            {
                assert(indx>0); assert(indx<=Size);
                return cxx[indx];
            }


            inline ~Workspace() noexcept {
                
            }

        private:
            Y_Disable_Copy_And_Assign(Workspace);
            T * const cxx;
            void * wksp[ Alignment::WordsGEQ<N*sizeof(T)>::Count];
        };
    }

}

#endif // !Y_Memory_Workspace_Included

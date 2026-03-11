

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
        //______________________________________________________________________
        //
        //
        //
        //! static, aligned data for temporary storage
        //
        //
        //______________________________________________________________________
        template <typename T,const size_t N>
        class Workspace
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definition
            //
            //__________________________________________________________________
            static const size_t size = N; //!< number of elements

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with zeroed workspace
            inline  Workspace() noexcept :
            cxx(0), ptr(0), wksp()
            {
                Coerce(cxx) = ( Coerce(ptr) = static_cast<T *>( Y_BZero(wksp) )) - 1;
            }

            //! cleanup workspace
            inline ~Workspace() noexcept { Y_BZero(wksp); }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! access \param indx in [1:size] \return reference to slot[indx]
            T & operator[](const size_t indx) noexcept
            {
                assert(indx>0); assert(indx<=size);
                return cxx[indx];
            }

            //! access to direct memory \return static data address
            T * operator()(void) noexcept
            {
                return ptr;
            }


            
        private:
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            T * const cxx; //!< C++ handle
            T * const ptr; //!< C handle
            void *    wksp[ Alignment::WordsGEQ<N*sizeof(T)>::Count]; //!< static data

            Y_Disable_Copy_And_Assign(Workspace); //!< discarded

        };
    }

}

#endif // !Y_Memory_Workspace_Included

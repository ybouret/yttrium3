
//! \file

#ifndef Y_Memory_Zombie_Included
#define Y_Memory_Zombie_Included 1


#include "y/type/args.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/block/zero.h"

namespace Yttrium
{

    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Zombie(s) objects
        //
        //
        //______________________________________________________________________
        template <typename T, const size_t N=1>
        class Zombie
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type);        //!< aliases
            static const size_t size = N; //!< number of zombie(s)

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline explicit Zombie() noexcept : ptr(0), cxx(0), wksp()
            {
                Coerce(ptr) = static_cast<MutableType *>( Y_BZero(wksp) );
                Coerce(cxx) = ptr-1;
            }

            //! cleanup
            inline virtual ~Zombie() noexcept
            {
                Y_BZero(wksp);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! access zombie \param indx 1<=indx<=size \return indx-th zombie
            inline Type & operator[](const size_t indx) noexcept
            {
                assert(indx>=1); assert(indx<=size); return cxx[indx];
            }

            //! access const zombie \param indx 1<=indx<=size \return indx-th zombie
            inline ConstType & operator[](const size_t indx) const noexcept
            {
                assert(indx>=1); assert(indx<=size); return cxx[indx];
            }

            //! access static memory \return first zombie address
            inline MutableType * operator()(void)       noexcept { return ptr; }

            //! access static const memory \return first zombie address
            inline ConstType   * operator()(void) const noexcept { return ptr; }

        private:
            Y_Disable_Copy_And_Assign(Zombie); //!< discarded
            MutableType * const ptr; //!< base address
            MutableType * const cxx; //!< shifted address
            void * wksp[ Alignment::WordsGEQ<sizeof(T)*N>::Count ]; //!< static buffer
        };
    }

}

#endif // !Y_Memory_Zombie_Included


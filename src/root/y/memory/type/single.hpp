

//! \file

#ifndef Y_Memory_Single_Included
#define Y_Memory_Single_Included 1


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
        template <typename T>
        class Single
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type);        //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline explicit Single() noexcept :  addr(0), wksp()
            {
                Coerce(addr) = static_cast<MutableType*>( Y_BZero(wksp) );
            }

            //! cleanup
            inline ~Single() noexcept
            {
                Y_BZero(wksp);
                Coerce(addr) = 0;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! access static memory \return first zombie address
            inline MutableType * operator()(void)       noexcept { return addr; }

            //! access static const memory \return first zombie address
            inline ConstType   * operator()(void) const noexcept { return addr; }

        private:
            Y_Disable_Copy_And_Assign(Single); //!< discarded
            MutableType * const addr;
            void * wksp[ Alignment::WordsFor<T>::Count ]; //!< static buffer
        };
    }

}

#endif // !Y_Memory_Single_Included


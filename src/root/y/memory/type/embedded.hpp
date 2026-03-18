
//! \file

#ifndef Y_Memory_Embedded_Included
#define Y_Memory_Embedded_Included 1


#include "y/type/args.hpp"
#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"
#include <iostream>

namespace Yttrium
{

    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Embed type in memory
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Embedded
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! no argument new type setup \param where new type locaction
            inline explicit Embedded(void * const where) :
            addr( new ( Init(where) ) MutableType() )
            {

            }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename U>
            inline explicit Embedded(void * const where, U &u) :
            addr( new ( Init(where) ) MutableType(u) )
            {

            }

            template <typename U,typename V>
            inline explicit Embedded(void * const where, U &u, V &v) :
            addr( new ( Init(where) ) MutableType(u,v) )
            {

            }


            template <typename U,typename V, typename W>
            inline explicit Embedded(void * const where, U &u, V &v, W &w) :
            addr( new ( Init(where) ) MutableType(u,v,w) )
            {

            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            //! cleanup
            inline virtual ~Embedded() noexcept {
                Init( Destructed(addr) );
                Coerce(addr) = 0;
            }

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const Embedded &self)
            {
                return os << *self;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline Type      & operator*()       noexcept { assert(addr); return *addr; } //!< access \return type reference
            inline ConstType & operator*() const noexcept { assert(addr); return *addr; } //!< const access \return const type reference

            inline Type      * operator->()       noexcept { assert(addr); return addr; } //!< access \return type address
            inline ConstType * operator->() const noexcept { assert(addr); return addr; } //!< const access \return const type address


        private:
            Y_Disable_Copy_And_Assign(Embedded); //!< discarded
            MutableType * const addr;            //!< inner PERSISTENT address

            //! prepare space \param where type location \return clean region
            static inline void * Init(void * const where) noexcept
            {
                assert(0!=where);
                return Yttrium_BZero(where,sizeof(T));
            }
        };


    }

}

#endif // !Y_Memory_Embedded_Included


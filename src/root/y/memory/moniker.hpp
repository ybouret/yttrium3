
//! \file

#ifndef Y_Memory_Moniker_Included
#define Y_Memory_Moniker_Included 1


#include "y/type/args.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/block/zero.h"
#include "y/type/copy-of.hpp"
#include "y/type/destruct.hpp"
#include <iostream>

namespace Yttrium
{

    namespace Memory
    {

        template <typename T>
        class Moniker
        {
        public:
            Y_Args_Expose(T,Type);

            inline explicit Moniker() : addr(0), wksp()
            {
                new ( setup() ) MutableType();
            }

            template <typename U> inline
            explicit Moniker( U &u ) : addr(0), wksp()
            {
                new ( setup() ) MutableType(u);
            }

            template <typename U, typename V> inline
            explicit Moniker( U &u, V &v ) : addr(0), wksp()
            {
                new ( setup() ) MutableType(u,v);
            }

            template <typename U, typename V, typename W> inline
            explicit Moniker( U &u, V &v, W &w ) : addr(0), wksp()
            {
                new ( setup() ) MutableType(u,v,w);
            }

            inline virtual ~Moniker() noexcept
            {
                (void) Yttrium_BZero( Destructed(addr), sizeof(wksp) );
                Coerce(addr) = 0;
            }

            inline Moniker(const Moniker &moniker) : addr(0), wksp()
            {
                new ( setup() ) MutableType( *moniker );
            }

            inline friend std::ostream & operator<<(std::ostream &os, const Moniker &self)
            {
                return os << *self;
            }

            inline Type      & operator*()       noexcept { assert(addr); return *addr; }
            inline ConstType & operator*() const noexcept { assert(addr); return *addr; }

            inline Type      * operator->()       noexcept { assert(addr); return addr; }
            inline ConstType * operator->() const noexcept { assert(addr); return addr; }


        private:
            Y_Disable_Assign(Moniker);
            MutableType * const addr;
            void *wksp[ Alignment::WordsFor<T>::Count ];

            inline MutableType * setup() noexcept
            {
                return Coerce(addr) = static_cast<MutableType *>( Y_BZero(wksp) );
            }

        };
    }

}

#endif // !Y_Memory_Moniker_Included

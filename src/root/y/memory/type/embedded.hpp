
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

        template <typename T>
        class Embedded
        {
        public:
            Y_Args_Expose(T,Type);

            inline explicit Embedded(void * const where) :
            addr( new ( Init(where) ) MutableType() )
            {

            }

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


            inline virtual ~Embedded() noexcept
            {
                Init( Destructed(addr) );
                Coerce(addr) = 0;
            }

            inline friend std::ostream & operator<<(std::ostream &os, const Embedded &self)
            {
                return os << *self;
            }

            inline Type      & operator*()       noexcept { assert(addr); return *addr; }
            inline ConstType & operator*() const noexcept { assert(addr); return *addr; }

            inline Type      * operator->()       noexcept { assert(addr); return addr; }
            inline ConstType * operator->() const noexcept { assert(addr); return addr; }


        private:
            MutableType * const addr;
            Y_Disable_Copy_And_Assign(Embedded);
            static inline void * Init(void * const where) noexcept
            {
                assert(0!=where);
                return Yttrium_BZero(where,sizeof(T));
            }
        };


    }

}

#endif // !Y_Memory_Embedded_Included


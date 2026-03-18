//! \file

#ifndef Y_Memory_Small_House_Included
#define Y_Memory_Small_House_Included 1

#include "y/memory/small/arena.hpp"
#include "y/type/args.hpp"
#include "y/type/destruct.hpp"


namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            template <typename T>
            class House
            {
            public:
                Y_Args_Expose(T,Type);

                inline explicit House( Arena &userArena ) noexcept :
                arena( userArena )
                {
                    assert( arena.blockSize >= sizeof(Type) );
                }

                inline virtual ~House() noexcept
                {
                }

                inline void recycle(Type * const target) noexcept
                {
                    assert(0!=target);
                    MutableType * const tgt = Coerce(target);
                    arena.release( Destructed(tgt) );
                }

                inline Type * produce()
                {
                    void * addr = arena.acquire();
                    try {
                        return new (addr) MutableType();
                    }
                    catch(...) { arena.release(addr); throw;}
                }

                template <typename U>
                inline Type * produce( U &u )
                {
                    void * addr = arena.acquire();
                    try {
                        return new (addr) MutableType(u);
                    }
                    catch(...) { arena.release(addr); throw;}
                }

                template <typename U, typename V>
                inline Type * produce( U &u, V &v )
                {
                    void * addr = arena.acquire();
                    try {
                        return new (addr) MutableType(u,v);
                    }
                    catch(...) { arena.release(addr); throw;}
                }


                template <typename U, typename V, typename W>
                inline Type * produce( U &u, V &v, W &w )
                {
                    void * addr = arena.acquire();
                    try {
                        return new (addr) MutableType(u,v,w);
                    }
                    catch(...) { arena.release(addr); throw;}
                }




            private:
                Y_Disable_Copy_And_Assign(House);
                Arena & arena;
            };
        }

    }

}

#endif // !Y_Memory_Small_House_Included

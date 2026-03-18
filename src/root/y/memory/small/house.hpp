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

            //__________________________________________________________________
            //
            //
            //
            //! House arena to construct/destruct types
            //
            //
            //__________________________________________________________________
            template <typename T>
            class House
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type); //!< aliases

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param userArena PERSISTENT arena, arena.blocSize>=sizeof(Tyep)
                inline explicit House( Arena &userArena ) noexcept :
                arena( userArena ) {
                    assert( arena.blockSize >= sizeof(Type) );
                }

                //! cleanup
                inline virtual ~House() noexcept {}

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! recycle a previously produced object \param target alive type
                inline void recycle(Type * const target) noexcept
                {
                    assert(0!=target);
                    MutableType * const tgt = Coerce(target);
                    arena.release( Destructed(tgt) );
                }

                //! produce new type with default constructor \return new constructed type
                inline Type * produce()
                {
                    void * addr = arena.acquire();
                    try {
                        return new (addr) MutableType();
                    }
                    catch(...) { arena.release(addr); throw;}
                }

                //! produce new type with one argument
                /**
                 \param  u   argument
                 \return new constructed type
                 */
                template <typename U>
                inline Type * produce( U &u )
                {
                    void * addr = arena.acquire();
                    try {
                        return new (addr) MutableType(u);
                    }
                    catch(...) { arena.release(addr); throw;}
                }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
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
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)



            private:
                Y_Disable_Copy_And_Assign(House); //!< disarding
                Arena & arena;                    //!< support PERSISTENT arena
            };
        }

    }

}

#endif // !Y_Memory_Small_House_Included

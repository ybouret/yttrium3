
//! \file

#ifndef Y_Chemical_Roll_Included
#define Y_Chemical_Roll_Included 1

#include "y/chemical/type/indexed.hpp"

#include "y/container/associative/book.hpp"
#include "y/container/associative/hash/default-set.hpp"
#include "y/handy/basic/light/list.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! book+list of references
        //
        //
        //______________________________________________________________________
        template <typename T> class Roll : public Object, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef BookOf<const T,DefaultHashSet> BookType; //!< alias
            typedef Handy::BasicLightList<const T> ListType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit Roll() : Object(), book(), list() {} //!< setup
            inline virtual ~Roll() noexcept {}                   //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            inline virtual void free() noexcept
            {
                Coerce(book).free();
                Coerce(list).free();
            }

            //! inscribe Indexed type and kept list ordered \param t type to inscribe
            inline void inscribe(const T &t)
            {
                if( Coerce(book).write(t) ) {
                    try { Indexed::TopHSort( (Coerce(list) << t) ); }
                    catch(...) { Coerce(book).clear(t); throw; }
                } else {
                    assert(list.found(t));
                }
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const BookType book; //!< database
            const ListType list; //!< ordered content

        private:
            Y_Disable_Copy_And_Assign(Roll); //!< discarded
        };

    }

}

#endif // !Y_Chemical_Roll_Included

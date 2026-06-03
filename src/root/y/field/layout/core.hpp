//! file

#ifndef Y_Field_CoreLayout_Included
#define Y_Field_CoreLayout_Included 1

#include "y/field/sketch.hpp"
#include "y/hide.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Field
    {
        template <typename COORD> struct WidthFor;

        //! 1D
        template <> struct WidthFor<unit_t>
        {
            typedef size_t Type; //!< alias
        };

        //! [2|3|4]D
        template <template <typename> class VECT> struct WidthFor< VECT<unit_t> >
        {
            typedef VECT<size_t> Type; //!< alias
        };

        //______________________________________________________________________
        //
        //
        //
        //! Core Layout
        //
        //
        //______________________________________________________________________
        template <typename COORD>
        class CoreLayout : public Sketch
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned Dimensions = sizeof(COORD)/sizeof(unit_t); //!< alias
            typedef typename WidthFor<COORD>::Type Width; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param lo lower coordinates \param up upper coordinates
            inline explicit CoreLayout(const COORD &lo, const COORD &up) noexcept :
            lower(lo),
            upper(up),
            width( *static_cast<const Width *>(Zeroed) ),
            items( Setup(Hide::Cast<size_t>( &Coerce(width) ),
                         Hide::Cast<unit_t>( &Coerce(lower) ),
                         Hide::Cast<unit_t>( &Coerce(upper) ),
                         Dimensions) )
            {
            }

            //! cleanup
            inline virtual ~CoreLayout() noexcept {}

            //! display metrics
            inline friend std::ostream & operator<<(std::ostream &os, const CoreLayout &L) {
                return os << "|" << L.lower << "->" << L.upper << "#" << L.width << "|=" << L.items;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const COORD  lower; //!< (fixed) lower coordinates
            const COORD  upper; //!< (fixed) upper coordinates
            const Width  width; //!< width per dimension
            const size_t items; //!< total items

        private:
            Y_Disable_Assign(CoreLayout); //!< discarde
        };
    }
}

#endif // !Y_Field_CoreLayout_Included


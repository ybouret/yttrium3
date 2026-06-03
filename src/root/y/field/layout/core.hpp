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

        template <> struct WidthFor<unit_t>
        {
            typedef size_t Type;
        };

        template <template <typename> class VECT> struct WidthFor< VECT<unit_t> >
        {
            typedef VECT<size_t> Type;
        };

        template <typename COORD>
        class CoreLayout : public Sketch
        {
        public:
            static const unsigned Dimensions = sizeof(COORD)/sizeof(unit_t);
            typedef typename WidthFor<COORD>::Type Width;


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

            inline virtual ~CoreLayout() noexcept {}

            inline friend std::ostream & operator<<(std::ostream &os, const CoreLayout &L) {
                return os << "|" << L.lower << "->" << L.upper << "#" << L.width << "|=" << L.items;
            }

            const COORD  lower;
            const COORD  upper;
            const Width  width;
            const size_t items;
        private:
            Y_Disable_Assign(CoreLayout);
        };
    }
}

#endif // !Y_Field_CoreLayout_Included


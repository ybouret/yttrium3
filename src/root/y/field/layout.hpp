
//! file

#ifndef Y_Field_Layout_Included
#define Y_Field_Layout_Included 1

#include "y/field/layout/core.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Field
    {
        template <typename COORD>
        class Layout : public ArcPtr< CoreLayout<COORD> >
        {
        public:
            typedef CoreLayout<COORD>           LayoutType;
            typedef ArcPtr< CoreLayout<COORD> > PointerType;

            inline   Layout(const COORD lo, const COORD up) :
            PointerType( new LayoutType(lo,up) )
            {
            }

            inline Layout(const Layout &L) noexcept : PointerType(L) {}

            inline virtual ~Layout() noexcept {}
        private:
            Y_Disable_Assign(Layout);
        };
    }

}

#endif // !Y_Field_Layout_Included


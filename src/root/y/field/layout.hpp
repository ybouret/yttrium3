
//! file

#ifndef Y_Field_Layout_Included
#define Y_Field_Layout_Included 1

#include "y/field/layout/core.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Field
    {
        //______________________________________________________________________
        //
        //
        //
        //! Layout (shared core layout)
        //
        //
        //______________________________________________________________________
        template <typename COORD>
        class Layout : public ArcPtr< CoreLayout<COORD> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CoreLayout<COORD>           LayoutType;  //!< alias
            typedef ArcPtr< CoreLayout<COORD> > PointerType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param lo lower coordinates \param up upper coordinates
            inline Layout(const COORD lo, const COORD up) :
            PointerType( new LayoutType(lo,up) )
            {
            }

            //! duplicate \param L antoher layout
            inline Layout(const Layout &L) noexcept : PointerType(L) {}

            //! cleanup
            inline virtual ~Layout() noexcept {}

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline const COORD &lower() const noexcept { return (**this).lower; }
            inline const COORD &upper() const noexcept { return (**this).upper; }

            inline size_t bytesFor(const size_t bytesPerItem) const noexcept
            {
                return (**this).items * bytesPerItem;
            }

        private:
            Y_Disable_Assign(Layout); //!< discarded
        };
    }

}

#endif // !Y_Field_Layout_Included


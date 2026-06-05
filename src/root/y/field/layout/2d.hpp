//! file

#ifndef Y_Field_Layout2D_Included
#define Y_Field_Layout2D_Included 1

#include "y/field/layout/1d.hpp"
#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Field
    {
        typedef V2D<unit_t> Coord2D; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! 2D (shared) Layout
        //
        //
        //______________________________________________________________________
        class Layout2D : public Layout<Coord2D>
        {
        public:
            explicit Layout2D(const Coord2D, const Coord2D); //!< setup
            virtual ~Layout2D()        noexcept;             //!< cleanup
            Layout2D(const Layout2D &) noexcept;             //!< duplicate
            const Layout1D sub;                              //!< 1D projection
        private:
            Y_Disable_Assign(Layout2D);                      //!< dicarded
        };

    }

}

#endif // !Y_Field_Layout2D_Included


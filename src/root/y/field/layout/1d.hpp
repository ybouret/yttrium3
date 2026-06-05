

//! file

#ifndef Y_Field_Layout1D_Included
#define Y_Field_Layout1D_Included 1

#include "y/field/layout.hpp"

namespace Yttrium
{
    namespace Field
    {
        typedef unit_t Coord1D; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! 1D (shared) Layout
        //
        //
        //______________________________________________________________________
        class Layout1D : public Layout<Coord1D>
        {
        public:
            explicit Layout1D(const Coord1D, const Coord1D); //!< setup
            virtual ~Layout1D()        noexcept;             //!< cleanup
            Layout1D(const Layout1D &) noexcept;             //!< duplicate


        private:
            Y_Disable_Assign(Layout1D); //!< discared
        };

    }

}

#endif // !Y_Field_Layout1D_Included


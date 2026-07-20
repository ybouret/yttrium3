//! \file

#ifndef Y_Ink_Area_Included
#define Y_Ink_Area_Included 1

#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef V2D<unit_t> Vertex; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Area description
        //
        //
        //______________________________________________________________________
        class Area
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Area(const unit_t W, const unit_t H); //!< setup \param W width>0 \param H height>0
            virtual ~Area()                      noexcept; //!< cleanup
            Area(const Area &)                   noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Vertex getUpper()                const noexcept; //!< \return (xt,yt)
            bool   gotSameWxH(const Area &) const noexcept; //!< \return true iff same metrics

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const unit_t w;  //!< width
            const unit_t h;  //!< height
            const size_t n;  //!< items
            const unit_t xt; //!< width-1
            const unit_t yt; //!< heigh-1


        private:
            Y_Disable_Assign(Area); //!< discarded
        };

    }
}

#endif // !Y_Ink_Area_Included


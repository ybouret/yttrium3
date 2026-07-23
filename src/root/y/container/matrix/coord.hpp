

//! \file

#ifndef Y_Matrix_Coord_Included
#define Y_Matrix_Coord_Included 1

#include "y/mkl/v2d.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! helper to store row/colum indices
    //
    //
    //__________________________________________________________________________
    class MatrixCoord
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        MatrixCoord(const size_t i, const size_t j)  noexcept; //!< setup \param i row \param j column
        ~MatrixCoord()                               noexcept; //!< cleanup
        MatrixCoord(const MatrixCoord &)             noexcept; //!< duplicate
        MatrixCoord & operator=(const MatrixCoord &) noexcept; //!< assign \return *this
        Y_OSTREAM_PROTO(MatrixCoord);                          //!< displau

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! helper for tiles \param v computed from Tile2D/UpperDiagonalTile
        template <typename T> inline
        MatrixCoord( const V2D<T> v ) noexcept : r(v.y), c(v.x) {}

        friend bool operator==(const MatrixCoord &, const MatrixCoord &) noexcept; //!< \return true iff equal
        friend bool operator!=(const MatrixCoord &, const MatrixCoord &) noexcept; //!< \return true iff different

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        size_t r; //!< row index
        size_t c; //!< column index
    };
}

#endif // !Y_Matrix_Coord_Included


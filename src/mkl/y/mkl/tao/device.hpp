//! \file

#ifndef Y_MKL_Tao_Device_Included
#define Y_MKL_Tao_Device_Included 1

#include "y/concurrent/api/engine.hpp"
#include "y/concurrent/splitting/tiles1d.hpp"
#include "y/concurrent/splitting/tiles2d.hpp"
#include "y/concurrent/splitting/udts.hpp"
#include "y/cameo/addenda.hpp"
#include "y/container/matrix/metrics.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Tao
        {
            typedef Concurrent::Splitting::Scheme             Scheme; //!< alias

            //__________________________________________________________________
            //
            //
            // Defining Tiles
            //
            //__________________________________________________________________
            typedef Concurrent::Splitting::Tiles1D<size_t>    Tiles1D; //!< alias
            typedef Concurrent::Splitting::Tiles2D<size_t>    Tiles2D; //!< alias
            typedef Concurrent::Splitting::UpperDiagonalTiles UDTS;    //!< alias

            //__________________________________________________________________
            //
            //
            // Tile per Tiles
            //
            //__________________________________________________________________
            typedef Tiles1D::Tile   Tile1D;  //!< alias
            typedef Tiles2D::Tile   Tile2D;  //!< alias
            typedef UDTS::Tile      UDT;     //!< alias
            

            //__________________________________________________________________
            //
            //
            //
            //! Shared Memory and tiles management for a given SIMD
            //
            //
            //__________________________________________________________________
            class Device : public Concurrent::Engine
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Device(const Concurrent::Engine &); //!< setup from SIMD
                virtual ~Device() noexcept;                  //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Scheme  scheme;  //!< holds local memory
                Tiles1D tiles1d; //!< for vector/vector, matrix/vector ops
                Tiles2D tiles2d; //!< for matrix/matrix ops
                UDTS    udts;    //!< for upper diagonal ops

                //! remap 1D tiles \param numRows output number of rows \return tiles1d
                Tiles1D & remapT1D(const size_t numRows)         noexcept;

                //! remap 2D tiles \param metrics output metrics \return tiles2d
                Tiles2D & remapT2D(const MatrixMetrics &metrics) noexcept;

                //! remad UDTS \param n dimension of the square matrix \return udts
                UDTS    &  remapUDT(const size_t n) noexcept;


            private:
                Y_Disable_Copy_And_Assign(Device); //!< discarded


            };
        }
    }
}

#endif // !Y_MKL_Tao_Device_Included

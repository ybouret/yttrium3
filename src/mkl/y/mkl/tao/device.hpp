//! \file

#ifndef Y_MKL_Tao_Device_Included
#define Y_MKL_Tao_Device_Included 1

#include "y/concurrent/api/engine.hpp"
#include "y/concurrent/splitting/tiles1d.hpp"
#include "y/concurrent/splitting/tiles2d.hpp"
#include "y/concurrent/splitting/udts.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Tao
        {

            typedef Concurrent::Splitting::Tiles1D<size_t>    Tiles1D;
            typedef Concurrent::Splitting::Tiles2D<size_t>    Tiles2D;
            typedef Concurrent::Splitting::UpperDiagonalTiles UDTS;

            typedef Tiles1D::Tile Tile1D;
            typedef Tiles2D::Tile Tile2D;
            typedef UDTS::Tile    UDT;

            class Device : public Concurrent::Engine
            {
            public:
                class Code;
                
                explicit Device(const Concurrent::Engine &);
                virtual ~Device() noexcept;

                static size_t SizeOfCode() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Device);
                Code * const code;
            public:
                Concurrent::LocalCache &localCache;
                
            };
        }
    }
}

#endif // !Y_MKL_Tao_Device_Included

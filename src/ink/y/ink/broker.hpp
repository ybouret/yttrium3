
//! \file

#ifndef Y_Ink_Broker_Included
#define Y_Ink_Broker_Included 1

#include "y/ink/area.hpp"
#include "y/concurrent/splitting/tiles2d.hpp"
#include "y/concurrent/api/engine.hpp"

namespace Yttrium
{
    namespace Ink
    {
        typedef Concurrent::Engine                     Engine;
        typedef Concurrent::Splitting::Tile2D<unit_t>  Tile;
        typedef Concurrent::Splitting::Tiles2D<unit_t> Tiles;


        class Broker : public Engine, public Tiles
        {
        public:
            explicit Broker(const Engine &engine);
            virtual ~Broker() noexcept;
            
            void map(const Area &) noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(Broker);
            const Vertex v0;
        };
    }

}

#endif // !Y_Ink_Broker_Included


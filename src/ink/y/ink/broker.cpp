
#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {

        Broker:: Broker(const Engine &engine) :
        Engine(engine),
        Tiles(engine->size()),
        v0()
        {
            
        }

        Broker:: ~Broker() noexcept
        {
            
        }

        void Broker:: map(const Area &a) noexcept
        {
            remap(v0,Vertex(a.xt,a.yt));
        }
    }

}

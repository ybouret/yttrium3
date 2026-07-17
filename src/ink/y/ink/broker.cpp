
#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {

        Broker:: Broker(const Engine &engine) :
        Engine(engine),
        Tiles(engine->size(),(**this).sync()),
        v0()
        {
           
        }

        Broker:: ~Broker() noexcept
        {
            
        }

        void Broker:: map(const Area &a) noexcept
        {
            remap(v0,a.getUpper(),(**this).sync());
        }

        void Broker:: operator()(void)
        {
            Concurrent::SIMD &simd = **this;
            simd(*this, & Broker::call );
        }

        void Broker:: call(Context &ctx)
        {
            const Tile &tile = (*this)[ctx.indx];
            Y_Lock(ctx.sync);
            std::cerr << tile.c_str() << " : " << tile << std::endl;
        }

    }

}

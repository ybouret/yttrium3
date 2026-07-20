
#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {
		Lockable & Broker:: sync_() noexcept
		{
			return (**this).sync();
		}

        Broker:: Broker(const Engine &engine) :
        Engine(engine),
        Tiles(engine->size(),sync_()),
        v0()
        {
           
        }

        Broker:: ~Broker() noexcept
        {
            
        }

        void Broker:: map(const Area &a) noexcept
        {
            remap(v0,a.getUpper(),sync_());
        }

        void Broker:: operator()(void)
        {
            Concurrent::SIMD &self = **this;
            self(*this, & Broker::call );
        }

        void Broker:: call(Context &ctx)
        {
            const Tile &tile = (*this)[ctx.indx];
            Y_Lock(ctx.sync);
            std::cerr << tile.c_str() << " : " << tile << std::endl;
        }

    }

}


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
            typedef Concurrent::Context Context;

            explicit Broker(const Engine &engine);
            virtual ~Broker() noexcept;
            
            void map(const Area &) noexcept;


            void operator()(void)
            {
                Concurrent::SIMD &simd = **this;
                simd(*this, & Broker::call );
            }

            template <
            typename PIXMAP,
            typename OBJECT,
            typename METHOD>
            inline void run(PIXMAP &pixmap, OBJECT &host, METHOD meth)
            {
                map(pixmap);
                Wrap0<PIXMAP,OBJECT,METHOD>  wrap0 = { &pixmap, &host, meth };
                Concurrent::SIMD    & simd = **this;
                simd(*this, & Broker::call0<PIXMAP,OBJECT,METHOD>, wrap0);
            }


        private:
            Y_Disable_Copy_And_Assign(Broker);
            const Vertex v0;

            template <typename PIXMAP, typename OBJECT, typename METHOD>
            struct Wrap0
            {
                PIXMAP *pxm;
                OBJECT *host;
                METHOD  meth;
            };

            template <typename PIXMAP, typename OBJECT, typename METHOD> inline
            void call0(Context &ctx, Wrap0<PIXMAP,OBJECT,METHOD> &arg)
            {
                assert(arg.pxm);
                assert(arg.host);
                assert(arg.meth);
                Tile   & tile = (*this)[ctx.indx];
                OBJECT & host = *arg.host;
                METHOD   meth = arg.meth;
                (host.*meth)(tile,*arg.pxm);
            }


            void call(Context &ctx)
            {
                const Tile &tile = (*this)[ctx.indx];
                Y_Lock(ctx.sync);
                std::cerr << tile.c_str() << " : " << tile << std::endl;
            }


        };
    }

}

#endif // !Y_Ink_Broker_Included


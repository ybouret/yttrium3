
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
        typedef Concurrent::Engine                     Engine;  //!< alias
        typedef Concurrent::Splitting::Tile2D<unit_t>  Tile;    //!< alias
        typedef Concurrent::Splitting::Tiles2D<unit_t> Tiles;   //!< alias
        typedef Tile::Segment                          Segment; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Broker for tiled operations
        //
        //
        //______________________________________________________________________
        class Broker : public Engine, public Tiles
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Concurrent::Context Context; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Broker(const Engine &); //!< setup from existing engine
            virtual ~Broker() noexcept;      //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! remap tiles to area metrics
            void map(const Area &) noexcept;


            //! test call
            void operator()(void);

            //! operation on pixmap without argument
            /**
             call host.meth(tile,pixmap)
             \param pixmap derived from Area
             \param host   host object
             \param meth   object method
             */
            template <
            typename PIXMAP,
            typename OBJECT,
            typename METHOD>
            inline void operator()(PIXMAP &pixmap, OBJECT &host, METHOD meth)
            {
                map(pixmap);
                Wrap0<PIXMAP,OBJECT,METHOD>  wrap0 = { &pixmap, &host, meth };
                Concurrent::SIMD    & simd = **this;
                simd(*this, & Broker::call0<PIXMAP,OBJECT,METHOD>, wrap0);
            }

            //! operation on pixmap with argument
            /**
             call host.meth(tile,pixmap,source)
             \param pixmap derived from Area
             \param host   host object
             \param meth   object method
             \param source argument for method
             */
            template <
            typename PIXMAP,
            typename OBJECT,
            typename METHOD,
            typename SOURCE>
            inline void operator()(PIXMAP &pixmap, OBJECT &host, METHOD meth, SOURCE &source)
            {
                map(pixmap);
                Wrap1<PIXMAP,OBJECT,METHOD,SOURCE>  wrap1 = { &pixmap, &host, meth, &source };
                Concurrent::SIMD    & simd = **this;
                simd(*this, & Broker::call1<PIXMAP,OBJECT,METHOD,SOURCE>, wrap1);
            }


            //! operation on pixmap with two argument
            /**
             call host.meth(tile,pixmap,source,extra1)
             \param pixmap derived from Area
             \param host   host object
             \param meth   object method
             \param source argument for method
             \param extra1 extra1 argument for method
             */
            template <
            typename PIXMAP,
            typename OBJECT,
            typename METHOD,
            typename SOURCE,
            typename EXTRA1>
            inline void operator()(PIXMAP &pixmap, OBJECT &host, METHOD meth, SOURCE &source, EXTRA1 &extra1)
            {
                map(pixmap);
                Wrap2<PIXMAP,OBJECT,METHOD,SOURCE,EXTRA1>  wrap2 = { &pixmap, &host, meth, &source, &extra1 };
                Concurrent::SIMD    & simd = **this;
                simd(*this, & Broker::call2<PIXMAP,OBJECT,METHOD,SOURCE,EXTRA1>, wrap2);
            }




#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
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

            template <typename PIXMAP, typename OBJECT, typename METHOD, typename SOURCE>
            struct Wrap1
            {
                PIXMAP * pxm;
                OBJECT * host;
                METHOD   meth;
                SOURCE * src;
            };

            template <typename PIXMAP, typename OBJECT, typename METHOD, typename SOURCE> inline
            void call1(Context &ctx, Wrap1<PIXMAP,OBJECT,METHOD,SOURCE> &arg)
            {
                assert(arg.pxm);
                assert(arg.host);
                assert(arg.meth);
                assert(arg.src);

                Tile   & tile = (*this)[ctx.indx];
                OBJECT & host = *arg.host;
                METHOD   meth =  arg.meth;
                (host.*meth)(tile,*arg.pxm,*arg.src);
            }

            template <typename PIXMAP, typename OBJECT, typename METHOD, typename SOURCE, typename EXTRA1>
            struct Wrap2
            {
                PIXMAP * pxm;
                OBJECT * host;
                METHOD   meth;
                SOURCE * src;
                EXTRA1 * ex1;
            };

            template <typename PIXMAP, typename OBJECT, typename METHOD, typename SOURCE,typename EXTRA1> inline
            void call2(Context &ctx, Wrap2<PIXMAP,OBJECT,METHOD,SOURCE,EXTRA1> &arg)
            {
                assert(arg.pxm);
                assert(arg.host);
                assert(arg.meth);
                assert(arg.src);
                assert(arg.ex1);

                Tile   & tile = (*this)[ctx.indx];
                OBJECT & host = *arg.host;
                METHOD   meth =  arg.meth;
                (host.*meth)(tile,*arg.pxm,*arg.src,*arg.ex1);
            }


            void call(Context &);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }

}

#endif // !Y_Ink_Broker_Included


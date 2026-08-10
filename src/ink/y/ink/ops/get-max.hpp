
//! \file

#ifndef Y_Ink_Ops_GetMax_Included
#define Y_Ink_Ops_GetMax_Included 1

#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {
        namespace Ops
        {

            template <typename PIXMAP> static inline
            void GetMaxCB(Tile &tile, PIXMAP &pixmap)
            {
                if(tile.isEmpty()) return;
                typedef typename PIXMAP::MutableType Type;
                Type &res = (tile.as<Type>() = pixmap(tile.start()));
                for(unit_t k=tile.span;k>0;--k)
                {
                    const Segment                s = tile[k];
                    const unit_t                 y = s.start.y;
                    const typename PIXMAP::Row & r = pixmap(y);
                    for(unit_t x=s.start.x,i=s.width;i>0;--i,++x)
                         InSituMax(res,r(x));
                }
            }

            template <typename PIXMAP> inline
            typename PIXMAP::Type GetMax(Broker  & broker,
                                         PIXMAP  & pixmap)
            {
                typedef typename PIXMAP::MutableType Type;

                // prepare
                broker.map(pixmap);
                broker.ensureLocalCaches( sizeof(Type) );

                // collect each tile
                broker.apply(pixmap,GetMaxCB<PIXMAP>);

                // reduction
                size_t i = broker.size();
                Type   v = broker.sub(i).as<Type>();
                for(--i;i>0;--i) InSituMax(v, broker.sub(i).as<Type>() );
                return v;
            }

        }

    }

}

#endif // !Y_Ink_Ops_GetMax_Included



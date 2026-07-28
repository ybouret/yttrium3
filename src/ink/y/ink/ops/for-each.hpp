
//! \file

#ifndef Y_Ink_Ops_ForEach_Included
#define Y_Ink_Ops_ForEach_Included 1

#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {
        namespace Ops
        {


            template <typename PIXMAP, typename CONVERT, typename ORIGIN>
            inline void ForEach(Tile &tile, PIXMAP &pixmap, CONVERT &convert, ORIGIN &origin)
            {
                for(unit_t k=tile.span;k>0;--k)
                {
                    const Segment                s = tile[k];
                    const unit_t                 y = s.start.y;
                    typename       PIXMAP::Row & r = pixmap(y);
                    const typename ORIGIN::Row & o = origin(y);
                    for(unit_t x=s.start.x,i=s.width;i>0;--i,++x)
                        r(x) = convert(o(x));
                }
            }

        }

    }

}

#endif // !Y_Ink_Ops_ForEach_Included


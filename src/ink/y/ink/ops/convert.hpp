
//! \file

#ifndef Y_Ink_Ops_Convert_Included
#define Y_Ink_Ops_Convert_Included 1

#include "y/ink/ops/for-each.hpp"

namespace Yttrium
{
    namespace Ink
    {
        namespace Ops
        {

            template <typename PIXMAP, typename CONVERT, typename ORIGIN> inline
            void Convert(Broker  & broker,
                         PIXMAP  & pixmap,
                         CONVERT & convert,
                         ORIGIN  & origin)
            {

                broker.apply(pixmap,ForEach<PIXMAP,CONVERT,ORIGIN>,convert,origin);
            }

        }

    }

}

#endif // !Y_Ink_Ops_Convert_Included


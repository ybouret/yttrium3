#include "y/coven/colinear.hpp"
#include "y/utest/run.hpp"

#include "y/container/cxx/series.hpp"

using namespace Yttrium;

#define ALL_TESTS() \
Y_ASSERT( Coven::Colinear::Test(iarr,iarr) ); \
Y_ASSERT( Coven::Colinear::Test(iarr,uarr) ); \
Y_ASSERT( Coven::Colinear::Test(iarr,narr) ); \
Y_ASSERT( Coven::Colinear::Test(iarr,zarr) ); \
\
Y_ASSERT( Coven::Colinear::Test(uarr,iarr) ); \
Y_ASSERT( Coven::Colinear::Test(uarr,uarr) ); \
Y_ASSERT( Coven::Colinear::Test(uarr,narr) ); \
Y_ASSERT( Coven::Colinear::Test(uarr,zarr) ); \
\
Y_ASSERT( Coven::Colinear::Test(narr,iarr) ); \
Y_ASSERT( Coven::Colinear::Test(narr,uarr) ); \
Y_ASSERT( Coven::Colinear::Test(narr,narr) ); \
Y_ASSERT( Coven::Colinear::Test(narr,zarr) ); \
\
Y_ASSERT( Coven::Colinear::Test(zarr,iarr) );\
Y_ASSERT( Coven::Colinear::Test(zarr,uarr) );\
Y_ASSERT( Coven::Colinear::Test(zarr,narr) );\
Y_ASSERT( Coven::Colinear::Test(zarr,zarr) )


Y_UTEST(coven_colinear)
{

    CxxSeries<int>      iarr(10);
    CxxSeries<unsigned> uarr(10);
    CxxSeries<apn>      narr(10);
    CxxSeries<apz>      zarr(10);


    ALL_TESTS();

    {
        iarr << 1;
        uarr << 2;
        narr << 1;
        zarr << 2;
    }
    ALL_TESTS();
    



}
Y_UDONE()

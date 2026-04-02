
#include "y/calculus/meta2.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

#include <cstdio>

using namespace Yttrium;

#define Y_Check_CeilLog2(x)  Y_PRINTV(MetaCeilLog2<x>::Value); Y_ASSERT( (_1<<MetaCeilLog2<x>::Value) >= x )
#define Y_Check_ExactLog2(p) Y_CHECK( p == MetaExactLog2<(_1<<p)>::Value )

Y_UTEST(calculus_meta2)
{
    Core::Rand          ran;
    static const size_t _1 = 1;


    Y_Check_ExactLog2(0);
    Y_Check_ExactLog2(1);
    Y_Check_ExactLog2(2);
    Y_Check_ExactLog2(3);
    Y_Check_ExactLog2(4);
    Y_Check_ExactLog2(5);
    Y_Check_ExactLog2(6);
    Y_Check_ExactLog2(7);
    Y_Check_ExactLog2(8);
    Y_Check_ExactLog2(9);
    Y_Check_ExactLog2(10);
    Y_Check_ExactLog2(11);
    Y_Check_ExactLog2(12);
    Y_Check_ExactLog2(13);
    Y_Check_ExactLog2(14);
    Y_Check_ExactLog2(15);
    Y_Check_ExactLog2(16);
    Y_Check_ExactLog2(17);
    Y_Check_ExactLog2(18);
    Y_Check_ExactLog2(19);
    Y_Check_ExactLog2(20);
    Y_Check_ExactLog2(21);
    Y_Check_ExactLog2(22);
    Y_Check_ExactLog2(23);
    Y_Check_ExactLog2(24);
    Y_Check_ExactLog2(25);
    Y_Check_ExactLog2(26);
    Y_Check_ExactLog2(27);
    Y_Check_ExactLog2(28);
    Y_Check_ExactLog2(29);
    Y_Check_ExactLog2(30);
    std::cerr << std::endl;


    Y_Check_CeilLog2(0);
    Y_Check_CeilLog2(1);
    Y_Check_CeilLog2(2);
    Y_Check_CeilLog2(3);
    Y_Check_CeilLog2(4);
    Y_Check_CeilLog2(5);
    Y_Check_CeilLog2(6);
    Y_Check_CeilLog2(7);
    Y_Check_CeilLog2(8);



#include "check-ceil-log2.hxx"
    std::cerr << std::endl;

    if(false)
    {
        FILE * fp = fopen("check-ceil-log2.hxx","wt");
        size_t nt = 0;
        for(unsigned i=0;i<=10000;i += ran.in<size_t>(10,100))
        {
            fprintf(fp,"    Y_Check_CeilLog2(%u);\n",i);
            ++nt;
        }
        fclose(fp);
        std::cerr << "#checks=" << nt << std::endl;
    }


    Y_PRINTV( MetaNextPowerOfTwo<0>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<1>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<2>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<3>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<4>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<5>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<6>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<7>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<8>::Value );
    Y_PRINTV( MetaNextPowerOfTwo<1000>::Value );
    std::cerr << std::endl;

    //Y_PRINTV( MetaPrevPowerOfTwo<0>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<1>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<2>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<3>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<4>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<5>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<6>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<7>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<8>::Value );
    Y_PRINTV( MetaPrevPowerOfTwo<1000>::Value );

}
Y_UDONE()


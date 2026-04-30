
#include "y/apex/k/dft.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;
using namespace Apex;

namespace
{



    template <typename WORD, typename CORE>
    static inline
    void testDFT(Core::Rand &ran)
    {

        AutoPtr< Keg<WORD> > lhs = Keg<WORD>::MakeRandom(ran, ran.in<size_t>(0,40) );
        AutoPtr< Keg<WORD> > rhs = Keg<WORD>::MakeRandom(ran, ran.in<size_t>(0,40) );


        std::cerr << lhs->toHex() << std::endl;
        std::cerr << rhs->toHex() << std::endl;

        AutoPtr< Keg<WORD> > res = KegDFT::Compute(*lhs,*rhs);
        


    }

}

Y_UTEST(apex_k_dft)
{
    Core::Rand ran;
    testDFT<uint8_t,uint32_t>(ran);

}
Y_UDONE()


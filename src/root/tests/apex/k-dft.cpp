
#include "y/apex/k/dft.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/pointer/auto.hpp"
#include "y/apex/k/mul.hpp"
#include "y/apex/k/cmp.hpp"

using namespace Yttrium;
using namespace Apex;

namespace
{



    template <typename WORD, typename CORE>
    static inline
    void testDFT(Core::Rand &ran)
    {

        for(size_t iter=0;iter<16;++iter)
        {
            AutoPtr< Keg<WORD> > lhs = Keg<WORD>::MakeRandom(ran, ran.in<size_t>(0,100) );
            AutoPtr< Keg<WORD> > rhs = Keg<WORD>::MakeRandom(ran, ran.in<size_t>(0,100) );
            AutoPtr< Keg<WORD> > mul = KegMul::Compute<WORD,CORE>(lhs->word,lhs->words,rhs->word,rhs->words);


            std::cerr << "lhs=" << lhs->toHex() << std::endl;
            std::cerr << "rhs=" << rhs->toHex() << std::endl;
            std::cerr << "mul=" << mul->toHex() << std::endl;

            AutoPtr< Keg<WORD> > dft = KegDFT::Compute(*lhs,*rhs);
            std::cerr << "dft=" << dft->toHex() << std::endl;

            Y_ASSERT( __Zero__ == KegCmp::ResultFor(*mul,*dft) );
        }

        std::cerr << "Trace = " << KegDFT:: Trace << std::endl;

    }

}

Y_UTEST(apex_k_dft)
{
    Core::Rand ran;
    testDFT<uint8_t,uint32_t>(ran);

}
Y_UDONE()


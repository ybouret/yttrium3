#include "y/apex/k/add.hpp"
#include "y/apex/k/cmp.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"
#include "y/core/rand.hpp"
#include "y/system/wall-time.hpp"
#include "y/format/human-readable.hpp"

using namespace Yttrium;
using namespace Apex;

namespace
{
    template <typename WORD, typename CORE> static inline
    void TestKeg(Core::Rand &ran)
    {
        typedef Keg<WORD> KegType;
        System::WallTime  chrono;

        std::cerr << "-- Test Keg<" << KegType::WordBits << "> / " << sizeof(CORE)*8 << std::endl;
        Y_SIZEOF(KegType);
        

        const size_t nbits = sizeof(natural_t) * 8 -1;
        uint64_t     ell = 0;
        size_t       ops = 0;
        KegAdd::Trace = 0;
        do
        {
            ++ops;
            const natural_t lhs = ran.gen<natural_t>( ran.in<size_t>(0,nbits));
            const natural_t rhs = ran.gen<natural_t>( ran.in<size_t>(0,nbits));
            const natural_t sum = lhs+rhs;
            KegType L(CopyOf,lhs);
            KegType R; R.ld(rhs);
            const uint64_t       mark = System::WallTime::Ticks();
            AutoPtr< Keg<WORD> > S    = KegAdd:: Compute<WORD,CORE>(L.word,L.words,R.word,R.words);
            ell += System::WallTime::Ticks() - mark;
            const natural_t      s = S->getNatural();
            Y_ASSERT(sum==s);
        } while( chrono(ell) < 0.1L );

        const long double outer = (long double)ops / chrono(ell);
        std::cerr << "\t\touter::add64=" << HumanReadable( (uint64_t)outer ) << std::endl;
        if(KegAdd::Trace)
        {
            const long double inner = (long double)ops / chrono(KegAdd::Trace);
            std::cerr << "\t\tinner::add64=" << HumanReadable( (uint64_t)inner ) << std::endl;
        }

        std::cerr << std::endl;
    }

}

Y_UTEST(apex_keg)
{
    Core::Rand ran;
    Y_PRINTV(KegMetrics::MaxBytes);
    std::cerr << std::endl;
    
    TestKeg<uint8_t, uint16_t>(ran);
    TestKeg<uint8_t, uint32_t>(ran);
    TestKeg<uint8_t, uint64_t>(ran);
    TestKeg<uint16_t,uint32_t>(ran);
    TestKeg<uint16_t,uint64_t>(ran);
    TestKeg<uint32_t,uint64_t>(ran);


}
Y_UDONE()


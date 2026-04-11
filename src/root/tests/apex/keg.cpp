#include "y/apex/k/mul.hpp"
#include "y/apex/k/add.hpp"
#include "y/apex/k/sub.hpp"
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

        //----------------------------------------------------------------------
        //
        //
        // test add
        //
        //
        //----------------------------------------------------------------------
        {
            std::cerr << "-- testing additions" << std::endl;
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
            } while( chrono(ell) < 0.05L );

            const long double outer = (long double)ops / chrono(ell);
            std::cerr << "\t\touter::add64=" << HumanReadable( (uint64_t)outer ) << std::endl;
            if(KegAdd::Trace)
            {
                const long double inner = (long double)ops / chrono(KegAdd::Trace);
                std::cerr << "\t\tinner::add64=" << HumanReadable( (uint64_t)inner ) << std::endl;
            }
        }

        //----------------------------------------------------------------------
        //
        //
        // test comparisons
        //
        //
        //----------------------------------------------------------------------
        {
            std::cerr << "-- testing comparisons" << std::endl;
            for(size_t i=0;i<=64;++i)
            {
                for(size_t j=0;j<=64;++j)
                {
                    {
                        const natural_t lhs = ran.gen<natural_t>(i);
                        const natural_t rhs = ran.gen<natural_t>(j);
                        KegType L(CopyOf,lhs);
                        KegType R(CopyOf,rhs);
                        Y_ASSERT( Sign::Of(lhs,rhs) == KegCmp::Result(L.word,L.words,R.word,R.words) );
                    }
                }
            }
        }

        //----------------------------------------------------------------------
        //
        //
        // test sub
        //
        //
        //----------------------------------------------------------------------
        {
            std::cerr << "-- testing subtractions" << std::endl;
            uint64_t     ell = 0;
            size_t       ops = 0;
            KegSub::Trace   = 0;
            do
            {
                ++ops;
                natural_t lhs = ran.gen<natural_t>( ran.in<size_t>(0,64) );
                natural_t rhs = ran.gen<natural_t>( ran.in<size_t>(0,64) );
                if(lhs<rhs) Swap(lhs,rhs);
                const natural_t dif = lhs-rhs;
                const KegType L(CopyOf,lhs);
                const KegType R(CopyOf,rhs);
                Y_ASSERT(KegCmp::Result(L.word,L.words,R.word,R.words) != Negative);
                const uint64_t       mark = System::WallTime::Ticks();
                AutoPtr< Keg<WORD> > D = KegSub:: Compute<WORD,CORE>(L.word,L.words,R.word,R.words);
                ell += System::WallTime::Ticks() - mark;
                Y_ASSERT(dif == D->getNatural());
            } while( chrono(ell) < 0.05L );
            const long double outer = (long double)ops / chrono(ell);
            std::cerr << "\t\touter::sub64=" << HumanReadable( (uint64_t)outer ) << std::endl;
            if(KegSub::Trace)
            {
                const long double inner = (long double)ops / chrono(KegSub::Trace);
                std::cerr << "\t\tinner::sub64=" << HumanReadable( (uint64_t)inner ) << std::endl;
            }
        }

        //----------------------------------------------------------------------
        //
        //
        // test mul
        //
        //
        //----------------------------------------------------------------------
        {
            std::cerr << "-- testing multiplications" << std::endl;
            uint64_t     ell = 0;
            size_t       ops = 0;
            KegMul::Trace    = 0;
            do
            {
                ++ops;
                const natural_t      lhs = ran.gen<natural_t>( ran.in<size_t>(0,32) );
                const natural_t      rhs = ran.gen<natural_t>( ran.in<size_t>(0,32) );
                const natural_t      prod = lhs * rhs;
                const KegType        L(CopyOf,lhs);
                const KegType        R(CopyOf,rhs);
                const uint64_t       mark = System::WallTime::Ticks();
                AutoPtr< Keg<WORD> > P    = KegMul:: Compute<WORD,CORE>(L.word,L.words,R.word,R.words);
                ell += System::WallTime::Ticks() - mark;
                Y_ASSERT(P->getNatural() == prod);

            } while( chrono(ell) < 0.05L );
            const long double outer = (long double)ops / chrono(ell);
            std::cerr << "\t\touter::mul64=" << HumanReadable( (uint64_t)outer ) << std::endl;
            if(KegMul::Trace)
            {
                const long double inner = (long double)ops / chrono(KegMul::Trace);
                std::cerr << "\t\tinner::mul64=" << HumanReadable( (uint64_t)inner ) << std::endl;
            }
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


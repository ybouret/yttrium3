
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/coven/survey/positive.hpp"
#include "y/coven/survey/standard.hpp"
#include "y/coven/survey/inquiry.hpp"
#include "y/coven/compress.hpp"

#include "y/handy/joint/set.hpp"

#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"
#include "y/core/min.hpp"
#include "y/counting/combination.hpp"

using namespace Yttrium;

namespace {


    typedef Handy::JointSet<size_t,SingleThreadedClass> iSet;
    typedef iSet::CacheType                             iCache;


    template <typename T>
    static inline
    void fillSet(iSet &idb, const Readable<T> &nu)
    {
        for(size_t i=nu.size();i>0;--i)
        {
            if(nu[i] != 0)
            {
                idb |= i;
            }
        }
    }

    static inline
    void checkSys(const Matrix<int> &nu)
    {
        std::cerr << "nu=" << nu << std::endl;
        Matrix<apz> Q;
        Matrix<apz> mu;
        iCache      cache;
        iSet        source(cache);
        iSet        target(cache);

        {
            Y_ASSERT(MKL::OrthoSpace::Get(Q,nu));
            std::cerr << "Q=" << Q << std::endl;
            Coven::Inquiry<Coven::PositiveSurvey> survey(Q,2,Coven::Tribes::Optimizing);
            survey->print(std::cerr << "-- conservations: " << std::endl);
            std::cerr << "--" << std::endl;

        }

        {
            if(!Coven::Compress::Build(mu,nu,Coven::Compress::Transpose,2))
            {
                std::cerr << "empty mu!" << std::endl;
                return;
            }
            std::cerr << "mu   = " << mu << std::endl;
            const size_t p    = mu.rows;    // max
            const size_t m    = mu.cols;    // total space
            const size_t pmax = Min(p,m-1); // max possible rows to check together
            std::cerr << "p    = " << p << std::endl;
            std::cerr << "m    = " << m << std::endl;
            std::cerr << "pmax = " << pmax << std::endl;

            for(size_t k=1;k<=pmax;++k)
            {
                Combination comb(p,k);
                do
                {
                    std::cerr << "using " << comb << std::endl;
                    Matrix<apz> P(k,m);
                    for(size_t i=1;i<=k;++i)
                    {
                        P[i].load(mu[ comb[i] ]);
                    }
                    std::cerr << "\tP=" << P << std::endl;
                    if( !MKL::OrthoSpace::Get(Q,P)) { std::cerr << "\tno Q!" << std::endl; continue; }
                    std::cerr << "\tQ=" << Q << std::endl;
                    Coven::Inquiry<Coven::StandardSurvey> survey(Q,2,Coven::Tribes::Optimizing);
                    survey->print(std::cerr << "-- lincomb: " << std::endl);


                } while(comb.next());
            }



#if 0
            Coven::Inquiry<Coven::StandardSurvey> survey(mu,2,Coven::Tribes::Optimizing);
            survey->print(std::cerr << "-- combinations: " << std::endl);

            Coven::Vectors       stoi;
            const size_t         M = nu.cols;
            const Coven::Metrics m(M);
            for(const Coven::Vector *vn= (*survey)->head;vn;vn=vn->next)
            {
                source.free();
                target.free();
                const Coven::Vector & cf   = *vn;
                Coven::Vector       & st   = *stoi.pushTail( new Coven::Vector(m) );
                for(size_t i=cf.size();i>0;--i)
                {
                    const apz &factor = cf[i];
                    if(factor.s == __Zero__) continue;
                    const Readable<int> &nu_i = nu[i];
                    for(size_t j=M;j>0;--j)
                    {
                        const int n = nu_i[j];
                        if(n)
                        {
                            source |= j;
                            st[j] += n * factor;
                        }
                    }
                }
                st.update();
                for(size_t j=M;j>0;--j)
                {
                    if(st[j].s!=__Zero__) target |= j;
                }
                std::cerr << "source=" << source << std::endl;
                std::cerr << "target=" << target << std::endl;
                std::cerr << "st    =" << st << std::endl;

            }
#endif


        }

        std::cerr << std::endl;
    }
}

Y_UTEST(chem)
{




    {
        // H+ HO-
        Matrix<int> nu(1,2);
        nu[1][1] = 1; nu[1][2] = 1;
        checkSys(nu);
    }

    {
        // H+ HO- AH A-
        Matrix<int> nu(2,4);
        nu[1][1] = 1; nu[1][2] = 1;
        nu[2][1] = 1; nu[2][3] = -1; nu[2][4] = 1;
        checkSys(nu);
    }

    {
        // H+ HO- AH2 AH- A2-
        Matrix<int> nu(3,5);
        nu[1][1] = 1; nu[1][2] = 1;
        nu[2][1] = 1; nu[2][3] = -1; nu[2][4] = 1;
        nu[3][1] = 1; nu[3][4] = -1; nu[3][5] = 1;
        checkSys(nu);
    }


}
Y_UDONE()


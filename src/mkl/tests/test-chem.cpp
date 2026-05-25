
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/coven/survey/positive.hpp"
#include "y/coven/survey/standard.hpp"
#include "y/coven/survey/inquiry.hpp"
#include "y/coven/compress.hpp"

#include "y/handy/joint/set.hpp"

#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"

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




        Matrix<apz> Q;
        Matrix<apz> mu;
        std::cerr << "nu=" << nu << std::endl;
        iCache      cache;
        iSet        source(cache);
        iSet        target(cache);

        {
            Y_ASSERT(MKL::OrthoSpace::Get(Q,nu));
            std::cerr << "Q=" << Q << std::endl;
            Coven::Inquiry<Coven::PositiveSurvey> survey(Q,Coven::InquiryIncludesInitial,2,Coven::Tribes::Optimizing);
            survey->print(std::cerr << "-- conservations: " << std::endl);
        }

        {
            Coven::Compress(mu,nu,Coven::CompressTranspose);
            std::cerr << "mu = " << mu << std::endl;
            Coven::Inquiry<Coven::StandardSurvey> survey(mu,Coven::InquiryExcludesInitial,2,Coven::Tribes::Optimizing);
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


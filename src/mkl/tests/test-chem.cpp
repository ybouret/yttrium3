
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/coven/survey/positive.hpp"
#include "y/coven/survey/inquiry.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(chem)
{
    Matrix<apz> Q;

    {
        // H+ HO-
        Matrix<int> nu(1,2);
        nu[1][1] = 1; nu[1][2] = 1;
        std::cerr << "nu=" << nu << std::endl;
        Y_ASSERT(MKL::OrthoSpace::Get(Q,nu));
        std::cerr << "Q=" << Q << std::endl;
        Coven::Inquiry<Coven::PositiveSurvey> survey(Q,Coven::InquiryIncludesInitial);
        survey->print(std::cerr << "-- ortho: " << std::endl);
        //rawPosInq.output(xml,nr);
    }

    {
        // H+ HO- AH A-
        Matrix<int> nu(2,4);
        nu[1][1] = 1; nu[1][2] = 1;
        nu[2][1] = 1; nu[2][3] = -1; nu[2][4] = 1;
        std::cerr << "nu=" << nu << std::endl;
        Y_ASSERT(MKL::OrthoSpace::Get(Q,nu));
        std::cerr << "Q=" << Q << std::endl;
        Coven::Inquiry<Coven::PositiveSurvey> survey(Q,Coven::InquiryIncludesInitial);
        survey->print(std::cerr << "-- ortho: " << std::endl);
    }

    {
        // H+ HO- AH2 AH- A2-
        Matrix<int> nu(3,5);
        nu[1][1] = 1; nu[1][2] = 1;
        nu[2][1] = 1; nu[2][3] = -1; nu[2][4] = 1;
        nu[3][1] = 1; nu[3][4] = -1; nu[3][5] = 1;
        std::cerr << "nu=" << nu << std::endl;
        Y_ASSERT(MKL::OrthoSpace::Get(Q,nu));
        std::cerr << "Q=" << Q << std::endl;
        Coven::Inquiry<Coven::PositiveSurvey> survey(Q,Coven::InquiryIncludesInitial);
        survey->print(std::cerr << "-- ortho: " << std::endl);
    }


}
Y_UDONE()


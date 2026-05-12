
#include "y/coven/survey/inquiry.hpp"
#include "y/coven/survey/standard.hpp"
#include "y/coven/survey/positive.hpp"

#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

Y_UTEST(coven_inquiry)
{
    Core::Rand    ran;
    const size_t  nr = argc>1 ? ASCII::Convert::To<size_t>(argv[1],"nr",0) : 5;
    const size_t  nc = argc>2 ? ASCII::Convert::To<size_t>(argv[2],"nc",0) : 4;
    const int     va = argc>3 ? ASCII::Convert::To<int>(argv[3],"va",0) : 1;

    bool     verbose = true;
    XML::Log xml(std::cerr,verbose);
    {
        Matrix<int>                           mu(nr,nc);
        for(size_t i=1;i<=nr;++i)
            for(size_t j=1;j<=nc;++j)
                mu[i][j] = ran.in<int>(-va,va);
        std::cerr << "mu=" << mu << std::endl;

        {
            (std::cerr << "-- raw standard inquiry" << std::endl).flush();
            Coven::Inquiry<Coven::StandardSurvey> rawStdInq(mu,Coven::InquiryIncludesInitial,0x0);
            rawStdInq->print(std::cerr);
            rawStdInq.output(xml,nr);

            (std::cerr << "-- opt standard inquiry" << std::endl).flush();
            Coven::Inquiry<Coven::StandardSurvey> optStdInq(mu,Coven::InquiryIncludesInitial,Coven::Tribes::Optimizing);
            Y_CHECK(*rawStdInq==*optStdInq);
            optStdInq.output(xml,nr);
        }

        {
            (std::cerr << "-- raw positive inquiry" << std::endl).flush();
            Coven::Inquiry<Coven::PositiveSurvey> rawPosInq(mu,Coven::InquiryExcludesInitial,0x0);
            rawPosInq->print(std::cerr);
            rawPosInq.output(xml,nr);
        }

    }



}
Y_UDONE()


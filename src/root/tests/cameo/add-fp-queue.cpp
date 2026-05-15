
#include "y/cameo/add/static-fp-queue.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(cameo_add_fp_queue)
{

    {
        Cameo::FP_QueueSummator<float> fpq;
        std::cerr << fpq << std::endl;
        fpq << 1.2f << -2.7f << 0.01f;
        std::cerr << fpq << std::endl;
        Cameo::FP_QueueSummator<float> tmp(fpq);
        std::cerr << tmp << std::endl;
        std::cerr << fpq() << std::endl;
        std::cerr << tmp() << std::endl;
    }

    {
        Cameo::FP_QueueSummator< XReal<long double> > fpq;
        std::cerr << fpq << std::endl;
        fpq << 1.2f << -2.7f << 0.01f;
        std::cerr << fpq << std::endl;
        Cameo::FP_QueueSummator< XReal<long double> > tmp(fpq);
        std::cerr << tmp << std::endl;
        std::cerr << fpq() << std::endl;
        std::cerr << tmp() << std::endl;
    }

    {
        Cameo::StaticSummator<long double,4> fpq;
        fpq << 1 << -2 << -4 << 3;
        std::cerr << fpq << std::endl;
        Cameo::StaticSummator<long double,4> tmp(fpq);
        std::cerr << tmp << std::endl;
        std::cerr << fpq() << std::endl;
        std::cerr << tmp() << std::endl;
    }

}
Y_UDONE()


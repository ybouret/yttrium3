
#include "y/cameo/add/fp-queue.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(cameo_add_fp_queue)
{

    {
        Cameo::FP_QueueSummator<float> fpq;
        std::cerr << fpq << std::endl;
        fpq << 1.2f << -2.7f << 0.01f;
        std::cerr << fpq << std::endl;
        std::cerr << fpq() << std::endl;
    }

    {
        Cameo::FP_QueueSummator< XReal<double> > fpq;
        std::cerr << fpq << std::endl;
        fpq << 1.2f << -2.7f << 0.01f;
        std::cerr << fpq << std::endl;
        std::cerr << fpq() << std::endl;

    }

}
Y_UDONE()


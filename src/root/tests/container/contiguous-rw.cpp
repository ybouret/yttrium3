
#include "y/container/contiguous/rw.hpp"
#include "y/string.hpp"
#include "y/utest/run.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(container_contiguous_rw)
{
    ReadWriteContiguous<String> rws;
    (String&)rws = "Hello";

    std::cerr << rws << std::endl;

    Iter::Test::All(rws);

}
Y_UDONE()



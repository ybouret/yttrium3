#include "y/functor.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    static inline void print(const double x)
    {
        std::cerr << x << std::endl;
    }

    struct Dummy
    {
        int value;

        void print(double x)
        {
            std::cerr << "dummy: " << x << "  @" << value << std::endl;
        }

        void operator()(double x) const
        {
            std::cerr << "dummy( " << x << ") @" << value << std::endl;
        }
    };
}
Y_UTEST(functor)
{
    typedef Functor<void,TL1(double)> Func;
    Dummy dum = { 7 };
    Func  f = cfunctor(print);
    Func  g = dum;
    Func  h(&dum, & Dummy::print );

    std::cerr << "-- cfuntor" << std::endl;
    f(1.2);
    std::cerr << "-- callback " << std::endl;
    g(1.2);
    std::cerr << "-- command " << std::endl;
    h(1.2);
    std::cerr << std::endl;

    dum.value = 11;
    std::cerr << "-- callback " << std::endl;
    g(1.2);
    std::cerr << "-- command " << std::endl;
    h(1.2);


}
Y_UDONE()


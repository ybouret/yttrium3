#include "y/cameo/addition.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/apex/rational.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/v3d.hpp"


using namespace Yttrium;


namespace
{
    template <typename T>
    static inline
    void testScal()
    {
        Y_CHECK(Cameo::Addition<T>::IsSummator);
        Y_CHECK(Y_Is_SuperSubClass_Strict(Object,Cameo::Addition<T>));
        Y_SIZEOF(Cameo::Addition<T>);
        Cameo::Addition<T> xadd;

        xadd << 1 << 3 << 4 << 2;

        std::cerr << "xadd=" << xadd   << " / " << xadd.callSign() << std::endl;
        std::cerr << "sum =" << xadd() << std::endl;
    }

    template <typename T>
    static inline
    void testVect()
    {
        Y_CHECK(Cameo::Addition<T>::IsSummator);
        Y_CHECK(Y_Is_SuperSubClass_Strict(Object,Cameo::Addition<T>));
        Y_SIZEOF(Cameo::Addition<T>);

        Cameo::Addition<T> xadd;

        T        v;
        unsigned k = 0;
        for(size_t n=0;n<3;++n)

        {
            for(unsigned i=1;i<=T::Dimension;++i)
            {
                v[i] = k++;
            }
            xadd << v;
        }




        std::cerr << "xadd=" << xadd   << " / " << xadd.callSign() << std::endl;
        std::cerr << "sum =" << xadd() << std::endl;
    }

}


Y_UTEST(cameo_addition)
{

    testScal<apq>();
    testScal<apn>();
    testScal<apz>();
    testScal<int>();
    testScal<uint16_t>();

    testScal<float>();
    testScal<double>();
    testScal<long double>();

    testScal< XReal<float> >();
    testScal< XReal<double> >();
    testScal< XReal<long double> >();

    testVect< Complex<float> >();
    testVect< Complex< XReal<long double> > >();

    testVect< V3D<double> >();

}
Y_UDONE()


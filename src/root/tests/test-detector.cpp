#include "y/mkl/complex.hpp"
#include "y/mkl/v4d.hpp"

#include "y/utest/run.hpp"

#include "y/type/list.hpp"

#include <typeinfo>

// https://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class

// SFINAE stands for Substitution Failure is Not An Error

namespace Yttrium
{




    template <typename T, typename U = int>
    struct HasX {
        static const bool Value = false;
        static inline void Show()
        {
            std::cerr << "typeid(U)=" << typeid(U).name() << std::endl;
        }
    };

    template <typename T>
    struct HasX <T, decltype((void) T::x,0)>
    {
        static const bool Value = true;
        static inline void Show()
        {
            std::cerr << "TRUE" << std::endl;
        }
    };

    template <typename T, typename = int>
    struct HasDIMENSIONS { static const bool Value = false; };

    template <typename T>
    struct HasDIMENSIONS <T, decltype((void) T::DIMENSIONS, 0)>
    {
        static const bool Value = true;

    };





}

namespace
{
    struct A { int x; };
    struct B { int y; };


}

using namespace Yttrium;

Y_UTEST(detector)
{
    std::cerr << std::boolalpha;


    HasX<A>::Show();
    HasX<B>::Show();

    Y_PRINTV( HasX<A>::Value );
    Y_PRINTV( HasX<B>::Value );
    Y_PRINTV( HasX<bool>::Value );



    //Y_PRINTV( has_id<X>::value );
    //Y_PRINTV( has_id<Y>::value );


    //Y_PRINTV( HasDIMENSIONS<float>::Value );
    //Y_PRINTV( HasDIMENSIONS< Complex<float> >::Value );
    //Y_PRINTV( HasDIMENSIONS< V4D<int> >::Value );

}
Y_UDONE()

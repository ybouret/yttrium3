#include "y/type/detect/member.hpp"

#include "y/mkl/complex.hpp"
#include "y/mkl/v4d.hpp"

#include "y/utest/run.hpp"




// SFINAE stands for Substitution Failure is Not An Error

namespace
{
    struct A { int x; };
    struct B { int y; };
}


template <typename T>
struct HasTypedefFoobar {
    // Types "Yes" and "No" are guaranteed to have different sizes,
    // specifically sizeof(Yes) == 1 and sizeof(No) == 2.
    typedef char Yes[1];
    typedef char No[2];

    template <typename C>
    static Yes & test(typename C::Foobar*);

    template <typename>
    static No  & test(...);

    // If the "sizeof" of the result of calling test<T>(nullptr) is equal to
    // sizeof(Yes), the first overload worked and T has a nested type named
    // Foobar.
    static const bool value = (sizeof(test<T>(0)) == sizeof(Yes));
};

struct Foo {
    typedef float Foobar;
};

template <typename T>
struct HasX {
    // Types "Yes" and "No" are guaranteed to have different sizes,
    // specifically sizeof(Yes) == 1 and sizeof(No) == 2.
    typedef char Yes[1];
    typedef char No[2];

    template <typename C>
    static Yes & test( decltype(C::x) *);

    template <typename>
    static No  & test(...);

    // If the "sizeof" of the result of calling test<T>(0) is equal to
    // sizeof(Yes), the first overload worked and T has a member named 'x'
    static const bool Value = (sizeof(test<T>(0)) == sizeof(Yes));
};


template <typename T>
struct HasDIMENSIONS {
    // Types "Yes" and "No" are guaranteed to have different sizes,
    // specifically sizeof(Yes) == 1 and sizeof(No) == 2.
    typedef char Yes[1];
    typedef char No[2];

    template <typename C>
    static Yes & test( decltype(C::DIMENSIONS) *);

    template <typename>
    static No  & test(...);

    // If the "sizeof" of the result of calling test<T>(0) is equal to
    // sizeof(Yes), the first overload worked and T has a member named DIMENSIONS
    static const bool Value = (sizeof(test<T>(0)) == sizeof(Yes));
};

namespace {
    Y_DetectMember(Got,x);
    Y_DetectMember(Got,DIMENSIONS);

}



using namespace Yttrium;

Y_UTEST(detector)
{
    std::cerr << std::boolalpha;
    Y_PRINTV(HasTypedefFoobar<int>::value);
    Y_PRINTV(HasTypedefFoobar<Foo>::value);

    std::cerr << std::endl;
    Y_PRINTV(HasX<A>::Value);
    Y_PRINTV(HasX<B>::Value);
    Y_PRINTV(HasX<bool>::Value);

    std::cerr << std::endl;
    Y_PRINTV( HasDIMENSIONS<int>::Value );
    Y_PRINTV( HasDIMENSIONS< V2D<float> >::Value );

    std::cerr << std::endl;
    Y_PRINTV(Gotx<A>::Value);
    Y_PRINTV(Gotx<B>::Value);
    Y_PRINTV(Gotx<bool>::Value);

    std::cerr << std::endl;
    Y_PRINTV(GotDIMENSIONS<bool>::Value );
    Y_PRINTV(GotDIMENSIONS< Complex<float> >::Value );



}
Y_UDONE()

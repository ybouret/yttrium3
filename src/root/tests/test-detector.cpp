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
    struct HasX <T, decltype(T::x,0)>
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
struct GotX {
    // Types "Yes" and "No" are guaranteed to have different sizes,
    // specifically sizeof(Yes) == 1 and sizeof(No) == 2.
    typedef char Yes[1];
    typedef char No[2];

    template <typename C>
    static Yes & test( decltype(C::x) *);

    template <typename>
    static No  & test(...);

    // If the "sizeof" of the result of calling test<T>(0) is equal to
    // sizeof(Yes), the first overload worked and T has a nested type named
    // Foobar.
    static const bool Value = (sizeof(test<T>(0)) == sizeof(Yes));
};




using namespace Yttrium;

Y_UTEST(detector)
{
    std::cerr << std::boolalpha;
    Y_PRINTV(HasTypedefFoobar<int>::value);
    Y_PRINTV(HasTypedefFoobar<Foo>::value);

    Y_PRINTV(GotX<A>::Value);
    Y_PRINTV(GotX<B>::Value);
    Y_PRINTV(GotX<bool>::Value);



}
Y_UDONE()

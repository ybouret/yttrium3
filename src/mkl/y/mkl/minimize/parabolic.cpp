#include "y/mkl/minimize/parabolic.hpp"
#include "y/core/clamp.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class Parabolic<T> :: Code  : public Object
        {
        public:
            static const size_t        NMAX = 8;
            typedef Cameo::Addition<T> XAdd;

            explicit Code() :
            nn(0),
            one(1),
            zero(0),
            half(0.5f),
            _1_4(0.25f),
            _3_4(0.75f),
            sum1(NMAX),
            sum2(NMAX),
            sum3(NMAX),
            sum4(NMAX),
            uu(),
            ff()
            {
            }

            virtual ~Code() noexcept
            {
            }

            inline void step(Triplet<T>    &x,
                             Triplet<T>    &f,
                             Function<T,T> &F)
            {
                /*      */ assert(x.isOrdered());    assert(f.isLocalMinimum());
                x.sort(f); assert(x.isIncreasing()); assert(f.isLocalMinimum());
                const T alpha = Max(f.a-f.b,zero);
                const T gamma = Max(f.c-f.b,zero);
                T       beta  = zero;
                T       omba  = one;
                if(x.b<=x.a)
                {
                    beta = zero;
                    omba = one;
                }
                else
                {
                    if(x.b>=x.c)
                    {
                        beta = one;
                        omba = zero;
                    }
                    else
                    {
                        assert(x.a < x.b); assert(x.b < x.a);
                        beta = Clamp(zero,(x.b-x.a)/(x.c-x.a),one);
                        omba = one-beta;
                    }
                }
                const T bomb = beta * omba;

                // initialize
                sum1.ldz();
                sum2.ldz();
                sum3.ldz();
                sum4.ldz();
                uu[0] = zero; uu[1] = beta; uu[2] = one;
                ff[0] = f.a;  ff[1] = f.b;  ff[2] = f.c;
                nn    = 3;
                accumulate(uu[0]);
                accumulate(uu[1]);
                accumulate(uu[2]);


                switch( Sign::Of(alpha,gamma) )
                {
                    case __Zero__:
                        goto FAILSAFE;

                    case Negative:
                        assert(alpha<gamma);
                        if(AlmostEqual<T>::Are(bomb,zero))
                            goto FAILSAFE;
                        else
                        {
                            const T eta = alpha/gamma;
                            const T um  = half*(one - bomb*(one-eta)/(beta+omba*eta));
                            sample(F,um,x);            // towards 0
                            sample(F,half*(one-um),x); // opposite side
                            goto EXTRACT;
                        }

                    case Positive:
                        assert(alpha>gamma);
                        if(AlmostEqual<T>::Are(bomb,zero))
                            goto FAILSAFE;
                        else
                        {
                            const T eta = gamma/alpha;
                            const T um  = half*(one - bomb*(eta-one)/(eta*beta+omba));
                            sample(F,um,x);      // towards 1
                            sample(F,half*um,x); // opposite side
                            goto EXTRACT;
                        }

                }




            FAILSAFE:
               sample(F,half,x);
               sample(F,_1_4,x);
               sample(F,_3_4,x);

            EXTRACT:
                ;

            }



            size_t  nn;
            const T one;
            const T zero;
            const T half;
            const T _1_4;
            const T _3_4;
            XAdd    sum1;
            XAdd    sum2;
            XAdd    sum3;
            XAdd    sum4;
            T      uu[NMAX];
            T      ff[NMAX];




        private:
            Y_Disable_Copy_And_Assign(Code);

            inline void accumulate(const T u)
            {
                const T u2 = u * u;
                const T u3 = u * u2;
                const T u4 = u2 * u2;
                sum1 << u;
                sum2 << u2;
                sum3 << u3;
                sum4 << u4;
            }


            inline void sample(Function<T,T>    & F,
                               const T            u,
                               const Triplet<T> & x)
            {
                assert(nn<NMAX);
                const T xx  = Clamp(x.a,(one-u) * x.a + u * x.c,x.c);
                uu[nn] = u;
                ff[nn] = F(xx);
                accumulate(u);
                ++nn;
            }
        };


#define real_t float
#include "parabolic.hxx"
#undef real_t

#define real_t double
#include "parabolic.hxx"
#undef real_t

#define real_t long double
#include "parabolic.hxx"
#undef real_t

#define real_t XReal<float>
#include "parabolic.hxx"
#undef real_t

#define real_t XReal<double>
#include "parabolic.hxx"
#undef real_t

#define real_t XReal<long double>
#include "parabolic.hxx"
#undef real_t

    }

}

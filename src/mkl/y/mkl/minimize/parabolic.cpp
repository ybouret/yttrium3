#include "y/mkl/minimize/parabolic.hpp"
#include "y/core/clamp.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/cameo/addition.hpp"
#include "y/core/hsort.hpp"
#include "y/stream/libc/output.hpp"

#include <iomanip>

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
            uu(),
            ff(),
            verbose(false)
            {
            }

            virtual ~Code() noexcept
            {
            }

            inline T step(Triplet<T>    &x,
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
                        assert(x.a < x.b);
                        assert(x.b < x.c);
                        beta = Clamp(zero,(x.b-x.a)/(x.c-x.a),one);
                        omba = one-beta;
                    }
                }
                const T bomb = beta * omba;
                if(verbose) {
                    std::cerr << "-- Parabolic::Step(" << x << "," << f << ")" << std::endl;
                    std::cerr << "-- alpha = " << alpha << " | gamma = " << gamma << std::endl;
                    std::cerr << "-- beta  = " << beta << " @" << x.b << std::endl;
                }

                // initialize
                uu[0] = zero; uu[1] = beta; uu[2] = one;
                ff[0] = f.a;  ff[1] = f.b;  ff[2] = f.c;
                nn    = 3;


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
                            const T um  = Clamp(zero,half*(one - bomb*(one-eta)/(beta+omba*eta)),half);
                            sample(F,um,x); // towards 0
                            //findShrinkage(beta,um,F,x);
                            goto EXTRACT;
                        }

                    case Positive:
                        assert(alpha>gamma);
                        if(AlmostEqual<T>::Are(bomb,zero))
                            goto FAILSAFE;
                        else
                        {
                            const T eta = gamma/alpha;
                            const T um  = Clamp(half,half*(one - bomb*(eta-one)/(eta*beta+omba)),one);
                            sample(F,um,x); // towards 1
                            //findShrinkage(beta,um,F,x);
                            goto EXTRACT;
                        }

                }




            FAILSAFE:
                if(verbose) std::cerr << "-- FAILSAFE!" << std::endl;
                sample(F,half,x);
                sample(F,_1_4,x);
                sample(F,_3_4,x);

            EXTRACT:
                Core::HSort::Make(uu,nn,Sign::Increasing<T>,ff);
                if(verbose)
                {
                    std::cerr << "-- Extracting from " << nn << " points" << std::endl;
                    for(size_t i=0;i<nn;++i)
                    {
                        const T xx  = u2x(uu[i],x);
                        std::cerr << std::setw(10) << uu[i] << " => " << std::setw(10) << xx << " => " << ff[i] << std::endl;
                    }
                }

                {
                    OutputFile fp("para-step.data");
                    for(size_t i=0;i<nn;++i)
                    {
                        const T xx  = u2x(uu[i],x);
                        fp("%g %g\n", (double)xx, (double) ff[i]);
                    }
                }
                return extract(x,f);
            }



            size_t  nn;
            const T one;
            const T zero;
            const T half;
            const T _1_4;
            const T _3_4;

            T      uu[NMAX];
            T      ff[NMAX];
            bool   verbose;



        private:
            Y_Disable_Copy_And_Assign(Code);

            void findShrinkage(const T            beta,
                               const T            um,
                               Function<T,T>    & F,
                               const Triplet<T> & x)

            {

                switch( Sign::Of(beta,um) )
                {
                    case __Zero__:
                        sample(F,half*um,x);
                        sample(F,half*(one+um),x);
                        break;

                    case Negative: assert(beta<um);
                        sample(F,half*(beta+um),x);
                        sample(F,half*(one+um),x);
                        break;

                    case Positive: assert(um<beta);
                        sample(F,half*um,x);
                        sample(F,half*(beta+um),x);
                        break;


                }

            }

            inline T u2x(const T u, const Triplet<T> &x) const noexcept
            {
                return Clamp(x.a,(one-u) * x.a + u * x.c,x.c);
            }

            inline void sample(Function<T,T>    & F,
                               const T            u,
                               const Triplet<T> & x)
            {
                assert(nn<NMAX);
                const T xx  = u2x(u,x);
                uu[nn] = u;
                ff[nn] = F(xx);
                if(verbose) std::cerr << "-- sample " << xx << " => " << ff[nn] << std::endl;
                ++nn;
            }

            inline T extract(Triplet<T> &x,
                             Triplet<T> &f) const
            {
                assert(nn>=3);
                const size_t top = nn-1;
                size_t       ib  = 1;
                T            fb  = ff[1];
                for(size_t i=2;i<top;++i)
                {
                    const T ft = ff[i];
                    if(ft<fb)
                    {
                        fb = ft;
                        ib = i;
                    }
                }

                const size_t ia = ib-1;
                const size_t ic = ib+1;
                const T xa = u2x(uu[ia],x);
                const T xb = u2x(uu[ib],x);
                const T xc = u2x(uu[ic],x);

                x.a = xa; f.a = ff[ia];
                x.b = xb; f.b = ff[ib];
                x.c = xc; f.c = ff[ic];

                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
                return x.c - x.a;
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

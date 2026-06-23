#include "y/mkl/minimize/parabolic.hpp"
#include "y/core/clamp.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/api/half.hpp"
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
            //C( (3.0f - sqrtf(5.0f))/2.0f ),
            //R(one-C),
            _1_4(0.25f),
            _3_4(0.75f),
            uu(),
            xx(),
            ff(),
            verbose(false)
            {
                Y_BZero(uu);
                Y_BZero(xx);
                Y_BZero(ff);

            }

            virtual ~Code() noexcept
            {
            }

            inline T step(Triplet<T>    &x,
                          Triplet<T>    &f,
                          Function<T,T> &F)
            {
                //--------------------------------------------------------------
                //
                //
                // initializing metrics
                //
                //
                //--------------------------------------------------------------

                /*      */ assert(x.isOrdered());    assert(f.isLocalMinimum());
                x.sort(f); assert(x.isIncreasing()); assert(f.isLocalMinimum());
                const T alpha = Max(f.a-f.b,zero);
                const T gamma = Max(f.c-f.b,zero);
                T       beta  = zero;
                T       omba  = one;
                if(x.b<=x.a)
                {
                    // beta = zero;
                    // omba = one;
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
                    std::cerr << "-- beta  = " << beta << std::endl;
                }

                //--------------------------------------------------------------
                //
                //
                // initialize sampling with endpoints
                //
                //
                //--------------------------------------------------------------
                uu[0] = zero;
                xx[0] = x.a;
                ff[0] = f.a;

                uu[1] = beta;
                xx[1] = x.b;
                ff[1] = f.b;


                uu[2] = one;
                xx[2] = x.c;
                ff[2] = f.c;

                nn    = 3;

                if( AlmostEqual<T>::Are(alpha,gamma) )
                {
                    std::cerr << "-- symetric => sample 1/2" << std::endl;
                    switch( Sign::Of(beta,half) )
                    {
                        case __Zero__: // beta==1/2
                            sample(F,_1_4,x);
                            sample(F,_3_4,x);
                            break;

                        case Negative: // sample (beta+1)/2
                            std::cerr << "-- between " << beta << " and " << one << std::endl;
                            assert(beta<half);
                            sample(F,Half<T>::Of(one,beta),x);
                            break;

                        case Positive: // sample beta/2
                            std::cerr << "-- between " << zero << " and " << beta << std::endl;
                            assert(beta>half);
                            sample(F,Half<T>::Of(beta),x);
                            break;
                    }

                }
                else
                {
                    if(alpha<gamma)
                    {
                        std::cerr << "-- towards 0" << std::endl;
                        const T eta = alpha/gamma;
                        const T um  = Clamp(zero,half*(one - bomb*(one-eta)/(beta+omba*eta)),half); // <1/2
                        sample(F,um,x); // towards 0
                    }
                    else
                    {
                        assert(gamma<alpha);
                        std::cerr << "-- towards 1" << std::endl;
                        const T eta = gamma/alpha;
                        const T um  = Clamp(half,half*(one + bomb*(one-eta)/(eta*beta+omba)),one); // > 1/2
                        sample(F,um,x); // towards 1
                    }
                    postProcess(F,beta,f.b,x);

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
            T      xx[NMAX];
            T      ff[NMAX];
            bool   verbose;



        private:
            Y_Disable_Copy_And_Assign(Code);

            inline void postProcess(Function<T,T>    & F,
                                    const T            beta,
                                    const T            fmin,
                                    const Triplet<T> & x)

            {
                const size_t top   = nn-1;
                const T      unew  = uu[top];
                const T      fnew  = ff[top];
                if(fnew<fmin)
                {
                    if(verbose) std::cerr << "-- new minimum" << std::endl;
                    switch( Sign::Of(unew,beta) )
                    {
                        case __Zero__:
                            sample(F, Half<T>::Of(beta),     x);
                            sample(F, Half<T>::Of(beta,one), x);
                            break;

                        case Negative:
                            assert(unew<beta);
                            sample(F, Half<T>::Of(unew), x);
                            break;

                        case Positive:
                            assert(unew>beta);
                            sample(F, Half<T>::Of(unew,one), x);
                            break;
                    }
                }
                else
                {
                    if(verbose) std::cerr << "-- overshoot" << std::endl;
                    exit(1);
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
                ff[nn] = F(xx[nn] = u2x(uu[nn]=u,x));
                if(verbose) std::cerr << "-- sample u=" << u << " => x=" << xx[nn] << " => " << ff[nn] << std::endl;
                ++nn;
            }
            
            inline T extract(Triplet<T> &x,
                             Triplet<T> &f)
            {
                assert(nn>=3);
                Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);




                // locate minimum
                size_t im = 0;
                T      fm = ff[0];
                const size_t nm = nn-1;
                for(size_t it=1;it<=nm;++it)
                {
                    const T ft = ff[it];
                    if(ft<fm)
                    {
                        fm = ft;
                        im = it;
                    }
                }

                if(0==im)
                {
                    // on the left
                    x.a = x.b = xx[0];
                    x.c = xx[1];
                    f.a = f.b = ff[0];
                    f.c = ff[1];
                    assert(x.isIncreasing());
                    assert(f.isLocalMinimum());
                }
                else
                {
                    if(nm==im)
                    {
                        // on the right
                        x.b = x.c = xx[im];
                        f.b = f.c = ff[im];
                        --im;
                        x.a = xx[im];
                        f.a = xx[im];
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                    else
                    {
                        // generic
                        assert(im>0); assert(im<nn-1);
                        const size_t ia=im-1;
                        x.load(&xx[ia]); assert(x.isIncreasing());
                        f.load(&ff[ia]); assert(f.isLocalMinimum());
                    }
                }
                if(verbose) std::cerr << "-- " << x << " => " << f << std::endl;



                {
                    OutputFile fp("para-step.data");
                    for(size_t i=0;i<nn;++i)
                    {
                        fp("%.15g %.15g\n", (double) xx[i], (double) ff[i]);
                    }
                    fp("%.15g %.15g\n", (double) xx[0], (double) ff[0]);
                    fp << "\n";
                    for(size_t i=1;i<=3;++i)
                    {
                        fp("%.15g %.15g\n", (double) x[i], (double) f[i]);
                    }
                    fp("%.15g %.15g\n", (double) x[1], (double) f[1]);

                }

                return x.c-x.a;
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

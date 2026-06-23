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
            static const size_t   NMAX = 8;
            static const unsigned W = 12;

            typedef Cameo::Addition<T> XAdd;

            explicit Code() :
            nn(0),
            one(1),
            zero(0),
            half(0.5f),
            _1_4(0.25f),
            _3_4(0.75f),
            xx(),
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

                //--------------------------------------------------------------
                //
                //
                // initialize metrics
                //
                //
                //--------------------------------------------------------------
                /*      */ assert(x.isOrdered());    assert(f.isLocalMinimum());
                x.sort(f); assert(x.isIncreasing()); assert(f.isLocalMinimum());
                const T alpha  = Max(f.a-f.b,zero);
                const T gamma  = Max(f.c-f.b,zero);
                T       beta   = zero;
                T       omba   = one;
                bool    middle = false;

                x.save(xx);
                f.save(ff);
                nn=3;


                if(x.b<=x.a)
                {
                    // beta = zero;
                    // omba = one;
                    assert(alpha<=zero);
                    ff[1] = F(xx[1] = Half<T>::Of(x.a,x.c) );
                    middle = true;
                }
                else
                {
                    if(x.b>=x.c)
                    {
                        beta = one;
                        omba = zero;
                        assert(gamma<=zero);
                        ff[1] = F(xx[1] = Half<T>::Of(x.a,x.c) );
                    }
                    else
                    {
                        assert(x.a < x.b);
                        assert(x.b < x.c);
                        beta = Clamp(zero,(x.b-x.a)/(x.c-x.a),one);
                        omba = one-beta;
                    }
                }
               // const T bomb = beta * omba;


                {
                    OutputFile fp("parabolic.data");
                    const unsigned np = 1000;
                    for(unsigned i=0;i<=np;++i)
                    {
                        const T  w = ( (double)i )/np;
                        const T  X = x.a * (one-w) + x.c * w;
                        fp("%.15g %.15g\n", (double) X, (double) F(X));
                    }
                }

                if(verbose) {
                    std::cerr << "-- Parabolic step" << std::endl;
                    std::cerr << "-- f(" << std::setw(W) << x.a << ")=" << std::setw(W) << f.a << " => alpha = " << alpha << std::endl;
                    std::cerr << "-- f(" << std::setw(W) << x.b << ")=" << std::setw(W) << f.b << " => beta  = " << beta << std::endl;
                    std::cerr << "-- f(" << std::setw(W) << x.c << ")=" << std::setw(W) << f.c << " => gamma = " << gamma << std::endl;
                }

                if(middle)
                {
                    // beta <=0 || beta >= 1
                    std::cerr << "-- middle was append" << std::endl;
                    std::cerr << "-- f(" << std::setw(W) << xx[1] << ")=" << std::setw(W) << ff[1]  << std::endl;
                    sample(_1_4, x, F);
                    sample(_3_4, x, F);
                }
                else
                {
                    if( AlmostEqual<T>::Are(alpha,gamma) )
                    {
                        //------------------------------------------------------
                        //
                        // symmetric guess
                        //
                        //------------------------------------------------------
                        sample(half,x,F);
                        switch( Sign::Of(beta,half) )
                        {
                            case Negative:
                                assert(beta<half);
                                sample(Half<T>::Of(x.b,x.c),F);
                                break;

                            case Positive:
                                assert(half<beta);
                                sample(Half<T>::Of(x.a,x.b),F);
                                break;

                            case __Zero__:
                                sample(Half<T>::Of(x.a,x.b),F);
                                sample(Half<T>::Of(x.b,x.c),F);
                                break;
                        }
                    }
                    else
                    {
                        //----------------------------------------------------------
                        //
                        // parabolic guess
                        //
                        //----------------------------------------------------------
                        if(alpha<gamma)
                        {
                            if(verbose) std::cerr << "-- towards x.a=" <<  x.a << std::endl;
                            const T eta = alpha/gamma;
                            const T um  = Clamp(zero,half*(one - beta*omba*(one-eta)/(beta+omba*eta)),half); // <1/2
                            sample(um,x,F); // towards 0
                        }
                        else
                        {
                            assert(gamma<alpha);
                            if(verbose) std::cerr << "-- towards x.c=" << x.c << std::endl;
                            const T eta = gamma/alpha;
                            const T um  = Clamp(half,half*(one + beta*omba*(one-eta)/(eta*beta+omba)),one); // > 1/2
                            sample(um,x,F); // towards 1
                        }
                    }
                }



                return one;
            }



            size_t  nn;
            const T one;
            const T zero;
            const T half;
            const T _1_4;
            const T _3_4;

            T      xx[NMAX];
            T      ff[NMAX];
            bool   verbose;



        private:
            Y_Disable_Copy_And_Assign(Code);


            void sample(const T xt, Function<T,T> &F)
            {
                ff[nn] = F(xx[nn] = xt);
                if(verbose) std::cerr << "-- f(" << std::setw(W) << xx[nn] << ")=" << std::setw(W) << ff[nn]  << std::endl;
                ++nn;
            }

            void sample(const T wc, const Triplet<T> &x, Function<T,T> &F)
            {
                assert(nn<NMAX);
                const T wa = one-wc;
                sample(Clamp(x.a,x.a*wa+x.c*wc,x.c),F);
            }



#if 0
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

                    //for(size_t i=1;i<=3;++i)
                    //{
                    //    fp("%.15g %.15g\n", (double) x[i], (double) f[i]);
                    //}
                    //fp("%.15g %.15g\n", (double) x[1], (double) f[1]);

                }

                return x.c-x.a;
            }
#endif

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

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
                    std::cerr << "-- beta  = " << beta << " @" << x.b << std::endl;
                }

                //--------------------------------------------------------------
                //
                //
                // initialize sampling
                //
                //
                //--------------------------------------------------------------
                uu[0] = zero; uu[1] = beta; uu[2] = one;
                xx[0] = x.a;  xx[1] = x.b;  xx[2] = x.c;
                ff[0] = f.a;  ff[1] = f.b;  ff[2] = f.c;
                nn    = 3;


                //--------------------------------------------------------------
                //
                //
                // build guess, with failsafe
                //
                //
                //--------------------------------------------------------------
                switch( Sign::Of(alpha,gamma) )
                {
                    case __Zero__: return failsafe(x,f,F);
                    case Negative:
                        assert(alpha<gamma);
                        if(AlmostEqual<T>::Are(bomb,zero))
                            return failsafe(x,f,F);
                        else
                        {
                            const T eta = alpha/gamma;
                            const T um  = Clamp(zero,half*(one - bomb*(one-eta)/(beta+omba*eta)),half);
                            const T fm = sample(F,um,x); // towards 0
                            if(fm<=f.b)
                            {
                                (void) sample(F,half*um,x); // towards 0
                            }
                            else
                            {
                                (void) sample(F,half*(beta+one),x); // backwards
                            }
                        } break;

                    case Positive:
                        assert(alpha>gamma);
                        if(AlmostEqual<T>::Are(bomb,zero))
                            return failsafe(x,f,F);
                        else
                        {
                            const T eta = gamma/alpha;
                            const T um  = Clamp(half,half*(one - bomb*(eta-one)/(eta*beta+omba)),one);
                            const T fm = sample(F,um,x); // towards 1
                            if( fm <= f.b )
                            {
                                (void) sample(F,half*(um+one),x); // towards 1
                            }
                            else
                            {
                                (void) sample(F,half*beta,x);    // backwards
                            }
                        } break;
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

            inline T failsafe(Triplet<T>    &x,
                              Triplet<T>    &f,
                              Function<T,T> &F)
            {
                if(verbose) std::cerr << "-- failsafe!" << std::endl;
                sample(F,half,x);
                sample(F,_1_4,x);
                sample(F,_3_4,x);
                return extract(x,f);
            }

            inline T u2x(const T u, const Triplet<T> &x) const noexcept
            {
                return Clamp(x.a,(one-u) * x.a + u * x.c,x.c);
            }

            inline T sample(Function<T,T>    & F,
                               const T            u,
                               const Triplet<T> & x)
            {
                assert(nn<NMAX);
                const T res = ( ff[nn] = F(xx[nn] = u2x(uu[nn]=u,x)) );
                if(verbose) std::cerr << "-- sample " << xx[nn] << " => " << ff[nn] << std::endl;
                ++nn;
                return res;
            }



            inline T extract(Triplet<T> &x,
                             Triplet<T> &f)
            {
                assert(nn>=3);
                Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);

                {
                    OutputFile fp("para-step.data");
                    for(size_t i=0;i<nn;++i)
                    {
                        fp("%.15g %.15g\n", (double) xx[i], (double) ff[i]);
                    }
                }

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

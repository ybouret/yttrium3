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
#include "y/xml/element.hpp"

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
            static const unsigned W    = 8;

            typedef Cameo::Addition<T> XAdd;

            explicit Code() :
            nn(0),
            one(1),
            zero(0),
            half(0.5f),
            _1_4(0.25f),
            _3_4(0.75f),
            xx(),
            ff()
            {

            }

            virtual ~Code() noexcept
            {
            }

            inline void step(XML::Log      & xml,
                             Triplet<T>    & x,
                             Triplet<T>    & f,
                             Function<T,T> & F)
            {

                //--------------------------------------------------------------
                //
                //
                // initialize triplet
                //
                //
                //--------------------------------------------------------------
                /*      */ assert(x.isOrdered());    assert(f.isLocalMinimum());
                x.sort(f); assert(x.isIncreasing()); assert(f.isLocalMinimum());

                Y_XML_Element_Attr(xml,ParabolicStep, Y_XML_Attr(x) << Y_XML_Attr(f) );

                {
                    OutputFile fp("parabolic.data");
                    const unsigned np = 1000;
                    for(unsigned i=0;i<=np;++i)
                    {
                        const T  w = ( (double)i )/np;
                        const T  X = x.a * (one-w) + x.c * w;
                        fp("%.15g %.15g\n", (double) X, (double) F(X));
                    }
                    OutputFile::Overwrite("para-step.data");
                }

                //--------------------------------------------------------------
                //
                //
                // Load triplet
                //
                //
                //--------------------------------------------------------------
                x.save(xx);
                f.save(ff);
                nn=3;

                //--------------------------------------------------------------
                //
                //
                // Reduction
                //
                //
                //--------------------------------------------------------------
                bool xsym = false;
                {
                    const T lw = Max(x.b-x.a,zero); // left  segment
                    const T rw = Max(x.c-x.b,zero); // right segment
                    switch( Sign::Of(lw,rw) )
                    {
                        case Negative:
                            assert(lw<rw); // reduce rw
                            sample(xml, Half<T>::Of(x.b,x.c), F);
                            break;

                        case Positive:
                            assert(rw<lw); // reduce lw
                            sample(xml, Half<T>::Of(x.a,x.b), F);
                            break;

                        case __Zero__: // symmetric
                            xsym = true;
                            sample(xml, Half<T>::Of(x.a,x.b), F);
                            sample(xml, Half<T>::Of(x.b,x.c), F);
                            break;
                    }
                }

                extract(xml,x,f);




#if 0
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
                    OutputFile::Overwrite("para-step.data");
                }

                if(verbose) {
                    std::cerr << "-- Parabolic step" << std::endl;
                    show(x.a,f.a);
                    show(x.b,f.b);
                    show(x.c,f.c);
                }

                if(middle)
                {
                    // beta <=0 || beta >= 1
                    std::cerr << "-- middle was append" << std::endl;
                    show(xx[1],ff[1]);
                    sample(_1_4, x, F);
                    sample(_3_4, x, F);
                    extract(x,f);
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
                        extract(x,f);
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
                        extract(x,f);
                        balance(x,f,F);
                    }
                }
#endif

            }



            size_t  nn;
            const T one;
            const T zero;
            const T half;
            const T _1_4;
            const T _3_4;
            T       xx[NMAX];
            T       ff[NMAX];



        private:
            Y_Disable_Copy_And_Assign(Code);

            static inline void show(XML::Log &xml, const T X, const T FX)
            {
                Y_XMLog(xml, "f(" << std::setw(W) << X << ") = " << std::setw(W) << FX );
            }

            inline void sample(XML::Log &xml, const T xt, Function<T,T> &F)
            {
                ff[nn] = F(xx[nn] = xt);
                show(xml,xx[nn],ff[nn]);
                ++nn;
            }

            inline void sample(const T wc, const Triplet<T> &x, Function<T,T> &F)
            {
                assert(nn<NMAX);
                const T wa = one-wc;
                return sample(Clamp(x.a,x.a*wa+x.c*wc,x.c),F);
            }




            inline void extract(XML::Log   &xml,
                                Triplet<T> &x,
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
                Y_XMLog(xml, "extract : x=" << x << "; f=" << f);



                {
                    OutputFile fp("para-step.data",true);
                    for(size_t i=0;i<nn;++i)
                    {
                        fp("%.15g %.15g 2\n", (double) xx[i], (double) ff[i]);
                    }
                    fp("%.15g %.15g 2\n", (double) xx[0], (double) ff[0]);
                    fp << "\n";


                    fp("%.15g %.15g 3\n", (double) x[1], (double) f[1]);
                    fp("%.15g %.15g 3\n", (double) x[2], (double) f[2]);
                    fp("%.15g %.15g 3\n", (double) x[3], (double) f[3]);
                    fp("%.15g %.15g 3\n", (double) x[1], (double) f[1]);
                    fp << "\n";

                }

            }



            inline void balance(Triplet<T>    & x,
                                Triplet<T>    & f,
                                Function<T,T> & F)
            {
                assert(x.isOrdered());
                assert(f.isLocalMinimum());
                while(true)
                {
                    const T lw = Max(x.b-x.a,zero);
                    const T rw = Max(x.c-x.b,zero);
                    T wmin = lw;
                    T wmax = rw;
                    if(wmin>wmax) Swap(wmin,wmax);
                    if(wmax<=wmin+wmin) break;

                    switch( Sign::Of(lw,rw) )
                    {
                        case __Zero__: return;
                        case Negative: assert(lw<rw); {
                            //if(verbose) std::cerr << "-- balance right" << std::endl;
                            const T xn = Half<T>::Of(x.b,x.c);
                            const T fn = F(xn);
                            show(xn,fn);
                            if(fn<=f.b)
                            {
                                x.a = x.b; f.a = f.b;
                                x.b = xn;  f.b = fn;
                                assert(x.isOrdered());
                                assert(f.isLocalMinimum());
                            }
                            else
                            {
                                x.c = xn; f.c = fn;
                                assert(x.isOrdered());
                                assert(f.isLocalMinimum());
                            }

                        } break;
                        case Positive: assert(rw<lw); {
                            //if(verbose) std::cerr << "-- balance left" << std::endl;
                            const T xn = Half<T>::Of(x.a,x.b);
                            const T fn = F(xn);
                            show(xn,fn);
                            if(fn<=f.b)
                            {
                                x.c = x.b; f.c = f.b;
                                x.b = xn;  f.b = fn;
                                assert(x.isOrdered());
                                assert(f.isLocalMinimum());
                            }
                            else
                            {
                                x.a = xn; f.a = fn;
                                assert(x.isOrdered());
                                assert(f.isLocalMinimum());
                            }
                        } break;
                    }

                }

                {
                    OutputFile fp("para-step.data",true);
                    fp("%.15g %.15g 4\n", (double) x[1], (double) f[1]);
                    fp("%.15g %.15g 4\n", (double) x[2], (double) f[2]);
                    fp("%.15g %.15g 4\n", (double) x[3], (double) f[3]);
                    fp("%.15g %.15g 4\n", (double) x[1], (double) f[1]);
                    fp << "\n";
                }

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

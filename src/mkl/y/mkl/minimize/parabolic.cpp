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
            static const size_t        NMAX = 8;
            static const size_t        W    = 8;
            typedef Cameo::Addition<T> XAdd;
            typedef Function<T,T>      FunctionType;

            explicit Code() :
            nn(0),
            one(  Numeric<T>::ONE ),
            zero( Numeric<T>::ZERO ),
            half( Numeric<T>::HALF ),
            xx(),
            ff()
            {

            }

            virtual ~Code() noexcept
            {
            }

#if 0
            inline void step2(XML::Log      & xml,
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
                        const T  w = ( (float)i )/np;
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
                    Y_XML_Element(xml,Linear);
                    {
                        const T lw = Max(x.b-x.a,zero); // left  segment
                        const T rw = Max(x.c-x.b,zero); // right segment
                        switch( Sign::Of(lw,rw) )
                        {
                            case Negative:
                                assert(lw<rw); // reduce rw
                                sample(xml, Half<T>(x.b,x.c), F);
                                break;

                            case Positive:
                                assert(rw<lw); // reduce lw
                                sample(xml, Half<T>(x.a,x.b), F);
                                break;

                            case __Zero__: // symmetric
                                xsym = true;
                                sample(xml, Half<T>(x.a,x.b), F);
                                sample(xml, Half<T>(x.b,x.c), F);
                                break;
                        }
                    }
                }

                //--------------------------------------------------------------
                //
                //
                // Parabolic inverse : we already processed the
                // x-symmetric case
                //
                //
                //--------------------------------------------------------------

                {
                    Y_XML_Element(xml,Quadratic);
                    if(x.b <= x.a )
                    {
                        // beta = 0 => predicts 1/2
                        Y_XMLog(xml, "-- beta=0");
                        sample(xml, Half<T>(x.b,x.c), F);
                    }
                    else
                    {
                        if(x.b>=x.c)
                        {
                            // beta = 1 => predicts 1/2
                            Y_XMLog(xml, "-- beta=1");
                            sample(xml, Half<T>(x.a,x.b), F);
                        }
                        else
                        {
                            const T beta  = Clamp(zero,(x.b-x.a)/(x.c-x.a),one);
                            const T omba  = Clamp(zero,one-beta,one);
                            const T alpha = Max(f.a-f.b,zero);
                            const T gamma = Max(f.c-f.b,zero);
                            switch( Sign::Of(alpha,gamma) )
                            {
                                case Negative: {
                                    Y_XMLog(xml, "-- towards x.a=" << x.a);
                                    const T eta = alpha/gamma;
                                    const T um  = Clamp(zero,half*(one - beta*omba*(one-eta)/(beta+omba*eta)),half); // <1/2
                                    sample(xml,um,x,F); // towards 0
                                } break;

                                case __Zero__: {
                                    Y_XMLog(xml, "-- take middle point (xsym=" << xsym << ")" );
                                    if(!xsym)
                                        sample(xml, Half<T>(x.a,x.b),F);
                                } break;


                                case Positive: {
                                    assert(gamma<alpha);
                                    Y_XMLog(xml, "-- towards x.c=" << x.c);
                                    const T eta = gamma/alpha;
                                    const T um  = Clamp(half,half*(one + beta*omba*(one-eta)/(eta*beta+omba)),one); // > 1/2
                                    sample(xml,um,x,F); // towards 1
                                } break;
                            }
                        }
                    }
                }

                extract(xml,x,f);
                balance(xml,x,f,F);

            }
#endif


            inline void step(XML::Log      & xml,
                             Triplet<T>    & x,
                             Triplet<T>    & f,
                             FunctionType  & F)
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
                x.save(xx);
                f.save(ff);
                nn=3;

                T    beta      = zero;
                if(x.b<=x.a)
                {
                    //----------------------------------------------------------
                    //
                    // beta=0
                    //
                    //----------------------------------------------------------
                    Y_XMLog(xml, "[beta<=0]");
                    sampleMiddle(xml,x,F);
                }
                else
                {
                    if(x.b>=x.c)
                    {
                        //------------------------------------------------------
                        //
                        // beta=1
                        //
                        //------------------------------------------------------
                        Y_XMLog(xml, "[beta>=1]");
                        sampleMiddle(xml,x,F);
                    }
                    else
                    {
                        //------------------------------------------------------
                        //
                        // 0<beta<1
                        //
                        //------------------------------------------------------
                        beta          = Clamp(zero,(x.b-x.a)/(x.c-x.a),one);
                        const T omb   = one-beta;
                        const T alpha = f.a-f.b;
                        const T gamma = f.c-f.b;
                        switch(Sign::Of(alpha,gamma))
                        {
                            case __Zero__:
                                Y_XMLog(xml, "[alpha==gamma]" );
                                sampleMiddle(xml,x,F);
                                break;

                            case Negative: assert(alpha<gamma); {
                                Y_XMLog(xml, "[alpha<gamma]" );
                                const T eta   = alpha/gamma;
                                const T twice = one-beta*omb*(one-eta)/(beta+omb*eta);
                                if( AlmostEqual<T>::Are(twice,one))
                                {
                                    Y_XMLog(xml,"[1/2_-]");
                                    sampleMiddle(xml,x,F);
                                }
                                else
                                {
                                    const T um = Clamp(zero,half*twice,one); assert(um<=half);
                                    sample(xml,um,F);
                                }
                            } break;

                            case Positive: assert(alpha>gamma); {
                                Y_XMLog(xml, "[alpha>gamma]");
                                const T eta = gamma/alpha;
                                const T twice = one + beta*omb*(one-eta)/(beta*eta+omb);
                                if( AlmostEqual<T>::Are(twice,one))
                                {
                                    Y_XMLog(xml,"[1/2_+]");
                                    sampleMiddle(xml,x,F);
                                }
                                else
                                {
                                    const T um = Clamp(zero,half*twice,one); assert(um<=half);
                                    sample(xml,um,F);
                                }
                            } break;

                        }
                    }
                }







                exit(1);
            }

            size_t  nn;
            const T one;
            const T zero;
            const T half;
            T       xx[NMAX];
            T       ff[NMAX];



        private:
            Y_Disable_Copy_And_Assign(Code);

            static inline void show(XML::Log &xml, const T X, const T FX)
            {
                Y_XMLog(xml, "[+] f(" << std::setw(W) << X << ") = " << std::setw(W) << FX );
            }



            inline void sample(XML::Log &xml, const T xt, FunctionType &F)
            {
                assert(nn<NMAX);
                ff[nn] = F(xx[nn] = xt);
                show(xml,xx[nn],ff[nn]);
                ++nn;
            }


            inline void sampleMiddle(XML::Log &xml, const Triplet<T> &x, FunctionType &F)
            {
                const T xm = x.middle(); sample(xml,xm,F);
            }

            inline void sampleGolden(XML::Log &xml, const Triplet<T> &x, FunctionType &F)
            {
                const T lw = Max(x.b-x.a,zero);
                const T rw = Max(x.c-x.b,zero);
                switch( Sign::Of(lw,rw) )
                {
                    case Negative: // reduce rw in [b:c]
                        assert(lw<rw);
                        sample(xml,Clamp(x.b,x.b+Numeric<T>::GOLDEN_C * rw, x.c),F);
                        break;

                    case Positive: // reduce lw in [a:b]
                        assert(lw>rw);
                        sample(xml,Clamp(x.a,x.b-Numeric<T>::GOLDEN_C * lw, x.b),F);
                        break;

                    case __Zero__: // reduce both
                        sample(xml,Clamp(x.b,x.b+Numeric<T>::GOLDEN_C * rw, x.c),F);
                        sample(xml,Clamp(x.a,x.b-Numeric<T>::GOLDEN_C * lw, x.b),F);
                        break;
                }
            }


            inline void sample(XML::Log &xml, const T wc, const Triplet<T> &x, FunctionType&F)
            {
                assert(nn<NMAX);
                const T wa = one-wc;
                return  sample(xml,Clamp(x.a,x.a*wa+x.c*wc,x.c),F);
            }

            inline void extract(XML::Log   &xml,
                                Triplet<T> &x,
                                Triplet<T> &f)
            {
                Y_XML_Element_Attr(xml, Extract, Y_XML_Attr(nn) );
                assert(nn>=3);
                Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);

                Core::Display(std::cerr << "xx=",xx,nn) << std::endl;
                Core::Display(std::cerr << "ff=",ff,nn) << std::endl;

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

                Y_XMLog(xml, "x=" << x << "; f=" << f);


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



            inline void balance(XML::Log      & xml,
                                Triplet<T>    & x,
                                Triplet<T>    & f,
                                Function<T,T> & F)
            {
                Y_XML_Element(xml,Balance);
                assert(x.isOrdered());
                assert(f.isLocalMinimum());
                while(true)
                {
                    const T lw = Max(x.b-x.a,zero);
                    const T rw = Max(x.c-x.b,zero);
                    T wmin = lw;
                    T wmax = rw;
                    if(wmin>wmax) Swap(wmin,wmax);
                    if(wmax<=wmin+wmin)
                        goto DONE;

                    switch( Sign::Of(lw,rw) )
                    {
                        case __Zero__:
                            return;

                        case Negative: assert(lw<rw); {
                            Y_XMLog(xml, "[<] balance right");
                            const T xn = Half<T>(x.b,x.c);
                            const T fn = F(xn);
                            show(xml,xn,fn);
                            if(fn<=f.b)
                            {
                                // new min
                                Y_XMLog(xml, "[<] new minimum");
                                x.a = x.b; f.a = f.b;
                                x.b = xn;  f.b = fn;
                                assert(x.isOrdered());
                                assert(f.isLocalMinimum());
                                goto DONE;
                            }
                            else
                            {
                                // shrink interval
                                Y_XMLog(xml, "[<] shrunk");
                                x.c = xn; f.c = fn;
                                assert(x.isOrdered());
                                assert(f.isLocalMinimum());
                            }

                        } break;

                        case Positive: assert(rw<lw); {
                            Y_XMLog(xml, "[>] balance left");
                            const T xn = Half<T>(x.a,x.b);
                            const T fn = F(xn);
                            show(xml,xn,fn);
                            if(fn<=f.b)
                            {
                                // new min
                                Y_XMLog(xml, "[>] new minimum");
                                x.c = x.b; f.c = f.b;
                                x.b = xn;  f.b = fn;
                                assert(x.isOrdered());
                                assert(f.isLocalMinimum());
                                goto DONE;
                            }
                            else
                            {
                                // shrink interval
                                Y_XMLog(xml, "[>] shrunk");
                                x.a = xn; f.a = fn;
                                assert(x.isOrdered());
                                assert(f.isLocalMinimum());
                            }
                        } break;
                    }
                }

            DONE:
                Y_XMLog(xml, "x=" << x << "; f=" << f);

                {
                    OutputFile fp("para-step.data",true);
                    fp("%.15g %.15g 4\n", (double) x[1], (double) f[1]);
                    fp("%.15g %.15g 4\n", (double) x[2], (double) f[2]);
                    fp("%.15g %.15g 4\n", (double) x[3], (double) f[3]);
                    fp("%.15g %.15g 4\n", (double) x[1], (double) f[1]);
                    fp << "\n";
                }

                //std::cerr << std::endl << " exit " << std::endl;
                //exit(1);

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

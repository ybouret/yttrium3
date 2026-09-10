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
            C(    Numeric<T>::GOLDEN_C ),
            xx(),
            ff()
            {

            }

            virtual ~Code() noexcept
            {
            }



            inline void grow(XML::Log      & xml,
                             Triplet<T>    & x,
                             Triplet<T>    & f,
                             FunctionType  & F)
            {
                assert(x.isIncreasing()); assert(f.isLocalMinimum());
                const T width = x.c-x.a;
                if(x.b<=x.a)
                {
                    //----------------------------------------------------------
                    //
                    //
                    // beta=0
                    //
                    //
                    //----------------------------------------------------------
                    Y_XMLog(xml, "[beta<=0]");
                    sample(xml,Clamp(x.a,x.a+C*width,x.c),F); // golden from left side
                }
                else
                {
                    if(x.b>=x.c)
                    {
                        //------------------------------------------------------
                        //
                        //
                        // beta=1
                        //
                        //
                        //------------------------------------------------------
                        Y_XMLog(xml, "[beta>=1]");
                        sample(xml,Clamp(x.a,x.c-C*width,x.c),F); // golden from right side
                    }
                    else
                    {
                        //------------------------------------------------------
                        //
                        //
                        // 0<beta<1
                        //
                        //
                        //------------------------------------------------------
                        const T        beta  = Clamp(zero,(x.b-x.a)/width,one);
                        const T        omb   = one-beta;
                        const T        alpha = f.a-f.b;
                        const T        gamma = f.c-f.b;

                        switch(Sign::Of(alpha,gamma))
                        {
                            case __Zero__:
                                Y_XMLog(xml, "[alpha=gamma]" );

                                if( AlmostEqual<T>::Are(beta,half) )
                                {
                                    golden(xml,x,F);
                                }
                                else
                                {
                                    Y_XMLog(xml, "[@middle]");
                                    sample(xml,Clamp(x.a,x.a+half*width,x.c),F);
                                }

                                break;

                            case Negative: {
                                assert(alpha<gamma);
                                Y_XMLog(xml, "[alpha<gamma]" );
                                const T eta = alpha/gamma;
                                const T u_m = Clamp(zero,half*(one-beta*omb*(one-eta)/(beta+omb*eta)),one);
                                sample(xml,u_m,x,F);
                            } break;

                            case Positive: {
                                Y_XMLog(xml, "[alpha>gamma]");
                                const T eta = gamma/alpha;
                                const T u_m = Clamp(zero,half*(one + beta*omb*(one-eta)/(beta*eta+omb)),one);
                                sample(xml,u_m,x,F);
                            } break;


                        }
                    }
                }
            }

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


                {
                    OutputFile fp("para-func.data");
                    const unsigned np = 100;
                    for(unsigned i=0;i<=np;++i)
                    {
                        const T XX = x.a + ((T)i) * (x.c-x.a) / (T)np;
                        const T FF = F(XX);
                        fp("%.15g %.15g\n", (double)XX, (double)FF);
                    }
                    OutputFile::Overwrite("para-step.data");
                }


                //--------------------------------------------------------------
                //
                //
                // grow sample
                //
                //
                //--------------------------------------------------------------
                grow(xml,x,f,F);

                //--------------------------------------------------------------
                //
                //
                // extract estimate
                //
                //
                //--------------------------------------------------------------
                extract(xml,x,f);



                exit(1);
            }

            size_t  nn;        //!< sampling size
            const T one;       //!< 1
            const T zero;      //!< 0
            const T half;      //!< 1/2
            const T C;         //!< GOLDEN_C
            T       xx[NMAX];
            T       ff[NMAX];



        private:
            Y_Disable_Copy_And_Assign(Code);

            static inline void show(XML::Log &xml, const T X, const T FX)
            {
                Y_XMLog(xml, "[+] f(" << std::setw(W) << X << ") = " << std::setw(W) << FX );
            }

            inline void sample(XML::Log     & xml,
                               const T        xt,
                               FunctionType & F)
            {
                assert(nn<NMAX);
                ff[nn] = F(xx[nn] = xt);
                show(xml,xx[nn],ff[nn]);
                ++nn;
            }

            inline void goldenLeft(XML::Log &xml, const Triplet<T> &x, FunctionType &F)
            {
                sample(xml,Clamp(x.a,x.b-C*(x.b-x.a),x.b),F); // golden left
            }

            inline void goldenRight(XML::Log &xml, const Triplet<T> &x, FunctionType &F)
            {
                sample(xml,Clamp(x.b,x.b+C*(x.c-x.b),x.c),F); // golden right
            }

            inline void golden(XML::Log &xml, const Triplet<T> &x, FunctionType &F)
            {
                Y_XMLog(xml, "[>shrink<]");
                goldenLeft(xml,x,F);
                goldenRight(xml,x,F);
            }


            inline void sample(XML::Log &xml, const T u_m, const Triplet<T> &x, FunctionType &F)
            {
                const T x_m = Clamp(x.a,x.a+u_m*(x.c-x.a),x.c); // prediction

                switch(Sign::Of(x_m,x.b))
                {
                    case Negative:
                        assert(x_m<x.b);
                        sample(xml,x_m,F);
                        break;

                    case Positive:
                        assert(x_m>x.b);
                        sample(xml,x_m,F);
                        break;

                    case __Zero__: // same point as x.b
                        golden(xml,x,F);
                        break;
                }
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

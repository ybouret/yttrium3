
#include "y/mkl/function-wrapper-1d.hpp"
#include "y/mkl/triplet.hpp"
#include "y/xml/log.hpp"



namespace Yttrium
{
    namespace MKL
    {


        template <typename T>
        class Quadratic
        {
        public:
            class Code;


            explicit Quadratic() : code( new Code() )
            {
            }

            virtual ~Quadratic() noexcept
            {
                Destroy(code);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! refine local minimum position
            /**
             \param xml output
             \param x   initial coordinates
             \param f   initial values
             \param F   primary function
             */
            void step(XML::Log      &xml,
                      Triplet<T>    &x,
                      Triplet<T>    &f,
                      Function<T,T> &F)
            {
                assert(code);
                code->step(xml,x,f,F);
            }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename FUNCTION>   inline
            void step(XML::Log   & xml,
                      FUNCTION   & F,
                      Triplet<T> & x,
                      Triplet<T> & f)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return step(xml,x,f,FW);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        private:
            Y_Disable_Copy_And_Assign(Quadratic);
            Code * const code;
        };



    }

}

#include "y/object.hpp"
#include "y/libc/block/zero.h"
#include "y/xml/element.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/api/half.hpp"
#include "y/cameo/multiplication.hpp"
#include "y/stream/libc/output.hpp"
#include "y/core/hsort.hpp"
#include "y/core/display.hpp"

namespace Yttrium
{
    namespace MKL
    {
        static bool Trace = true;

        template <typename T>
        class Quadratic<T>:: Code : public Object
        {
        public:
            static const size_t NMAX = 8;
            typedef Cameo::Multiplication<T> VMul;

            inline explicit Code() noexcept :
            Object(),
            nn(0),
            zero(Numeric<T>::ZERO),
            C(Numeric<T>::GOLDEN_C),
            one(Numeric<T>::ONE),
            vmul(NMAX),
            xx(),
            ff()
            {
            }


            inline virtual ~Code() noexcept {}

            static inline
            void Save(OutputStream  &  fp,
                      const T * const  px,
                      const T * const  py,
                      const size_t     pn,
                      const unsigned   color)
            {
                for(size_t i=0;i<pn;++i)
                {
                    fp("%.15g %.15g %u\n",(double)px[i], (double)py[i], color);
                }
                fp("%.15g %.15g %u\n",(double)px[0], (double)py[0], color);
                fp << "\n";

            }

            inline void step(XML::Log      &xml,
                             Triplet<T>    &x,
                             Triplet<T>    &f,
                             Function<T,T> &F)
            {


                // initialize with local minimum, assuming ordered x
                clear();

                assert(x.isOrdered());
                assert(f.isLocalMinimum());
                if(x.a>x.c)
                {
                    Swap(x.a,x.c);
                    Swap(f.a,f.c);
                    assert(x.isIncreasing());
                    assert(f.isLocalMinimum());
                }

                if(Trace)
                {
                    {
                        const unsigned np  = 100;
                        OutputFile fp("quad-data.dat");
                        fp("%.15g %.15g\n", (double)x.a, (double)f.a);
                        for(unsigned i=1;i<np;++i)
                        {
                            const T xt = x.a + ( (T) i ) * (x.c-x.a) / (T)np;
                            const T ft = F(xt);
                            fp("%.15g %.15g\n", (double)xt, (double)ft);
                        }
                        fp("%.15g %.15g\n", (double)x.c, (double)f.c);
                    }

                    lc=0;
                    {
                        OutputFile fp("quad-step.dat");
                        lc = 2;
                        Save(fp, &x[1], &f[1], 3, lc);
                    }
                }

                Y_XML_Element_Attr(xml,QuadraticStep,Y_XML_Attr(x) << Y_XML_Attr(f));

                // unfold cases
                if(x.b<=x.a)
                {
                    // beta <= 0
                    Y_XMLog(xml, "[<]");
                    sample(xml,x.b,f.b);
                    sample(xml,Clamp(x.b,x.b + Numeric<T>::GOLDEN_C * (x.c-x.b), x.c),F);
                    sample(xml,x.c,f.c);
                    assert(3==nn);
                }
                else
                {
                    if(x.b>=x.c)
                    {
                        // beta >= 1
                        Y_XMLog(xml, "[>]");
                        sample(xml,x.a,f.a);
                        sample(xml,Clamp(x.a,x.b-Numeric<T>::GOLDEN_C * (x.b-x.a), x.b),F);
                        sample(xml,x.b,f.b);
                        assert(3==nn);
                    }
                    else
                    {
                        // generic case
                        Y_XMLog(xml, "[*]");
                        sample(xml,x.a,f.a);
                        sample(xml,x.b,f.b);
                        sample(xml,x.c,f.c);
                        assert(3==nn);
                        const T alpha = f.a - f.b; assert(alpha>=zero);
                        const T gamma = f.c - f.b; assert(gamma>=zero);

                        if( AlmostEqual<T>::Are(alpha,gamma) )
                        {
                            // symmetrical
                            Y_XMLog(xml, "[=]");
                            sample(xml,Half<T>(x.a,x.c),F);
                        }
                        else
                        {
                            // generic
                            Y_XMLog(xml, "[#]");
                            const T width = x.c-x.a; assert(width>zero);
                            const T beta = Clamp(zero, (x.b-x.a)/(x.c-x.a), one);
                            const T omb  = one - beta;
                            const T den  = beta * gamma + omb * alpha;
                            const T sigma = f.c - f.a;
                            vmul.set(beta);
                            vmul.mul(omb);
                            vmul.mul(sigma);
                            const T twice = one - vmul()/den;
                            const T uquad = Half<T>(twice);
                            sample(xml,Clamp(x.a,x.a+uquad*width,x.c),F);
                        }

                    }
                }

                // extract 1/2
                extract(xml,x,f);

                // balance
                balance(xml,x,f,F);

                // extract 2/2
                extract(xml,x,f);

            }





            size_t   nn;       //!< number of store values
            const T  zero;     //!< Numeric<T>::ZERO>
            const T  C;        //!< Numeric<T>::GOLDEN_C
            const T  one;      //!< Numeric<T>::ONE>
            VMul     vmul;
            T        xx[NMAX]; //!< x values
            T        ff[NMAX]; //!< f value
            unsigned lc;      //!< line color

        private:
            Y_Disable_Copy_And_Assign(Code);

            inline void sample(XML::Log &xml, const T xnew, const T fnew)
            {
                assert(nn<NMAX);
                xx[nn] = xnew;
                ff[nn] = fnew;
                Y_XMLog(xml,"[+] F(" << xnew << ") = " << fnew);
                ++nn;
            }

            inline void sample(XML::Log &xml, const T xnew, Function<T,T> &F)
            {
                sample(xml,xnew,F(xnew));
            }



            inline void clear() noexcept
            {
                Y_BZero(xx);
                Y_BZero(ff);
                nn = 0;
            }


            inline void extract(XML::Log   & xml,
                                Triplet<T> & x,
                                Triplet<T> & f)
            {
                Y_XML_Element_Attr(xml,Extract, Y_XML_Attr(nn));
                Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);


#if !defined(NDEBUG)
                for(size_t i=1;i<nn;++i)
                    assert(xx[i-1]<=xx[i]);
#endif
                {
                    OutputFile fp("quad-step.dat",true);
                    lc += 2;
                    Save(fp, xx, ff, nn, lc);
                }

                

                size_t imin = 0;
                T      fmin = ff[0];
                for(size_t i=1;i<nn;++i)
                {
                    const T ftmp = ff[i];
                    if(ftmp<fmin)
                    {
                        imin = i;
                        fmin = ftmp;
                    }
                }
                std::cerr << "imin=" << imin << std::endl;


                // Locate left flat zone
                size_t nl = 0;
                {
                    const size_t nlMax = imin;
                    for(size_t i=1;i<=nlMax;++i)
                    {
                        if(ff[imin-i]>fmin) break;
                        nl = i;
                    }
                }


                // Locate right flat zone
                size_t nr = 0;
                {
                    const size_t nrMax = nn-imin;
                    for(size_t i=1;i<nrMax;++i)
                    {
                        if(ff[imin+i]>fmin) break;
                        nr = i;
                    }
                }


                // Compute flat zone
                const size_t flatZone = 1 + nl + nr;
                std::cerr << "flatZone = 1+" << nl << "+" << nr << " = " << flatZone << " @" << imin << std::endl;
                assert(flatZone<=nn);

                switch(flatZone)
                {
                    case 0: throw Specific::Exception("Quadratic::Extract", "corrupted!");
                    case 1: loadFZ1(x,f,imin);
                        break;

                    case 2: loadFZ2(x,f,imin-nl);
                        break;

                    case 3: {
                        const size_t org = imin-nl;
                        x.load(xx+org);
                        f.load(ff+org);
                    } break;

                    default:
                        abort();
                }

                {
                    OutputFile fp("quad-step.dat",true);
                    Save(fp, &x[1], &f[1], 3, lc+=2);
                }

            }


            //
            //
            // Extract new triplet with ONE exact numeric minimum
            //
            inline void loadFZ1(Triplet<T>    & x,
                                 Triplet<T>    & f,
                                 const size_t         im) noexcept
            {
                assert(nn>=3);
                if(0==im)
                {
                    //
                    // stuck on left : squeeze
                    //
                    x.a = x.b = xx[0];
                    f.a = f.b = ff[0];
                    x.c = xx[1];
                    f.c = ff[1];
                    assert(x.isIncreasing());
                    assert(f.isLocalMinimum());
                }
                else
                {
                    const size_t upper = nn-1;
                    if(upper==im)
                    {
                        //
                        // stuck on right : squeeze
                        //
                        const size_t lower=upper-1;
                        x.a = xx[lower]; f.a = ff[lower];
                        x.b = x.c = xx[upper];
                        f.b = f.c = ff[upper];
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                    else
                    {
                        //
                        // core : extract
                        //
                        const size_t j = im-1;
                        x.load(xx+j);
                        f.load(ff+j);
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                }
            }

            //__________________________________________________________________________
            //
            //
            // Extract new triplet with TWO exact numeric minima
            //
            //__________________________________________________________________________
            inline
            void loadFZ2(Triplet<T>    & x,
                         Triplet<T>    & f,
                         const size_t    org) noexcept
            {
                assert(nn>=3);

                if(org<=0)
                {
                    //------------------------------------------------------------------
                    //
                    // take left-most triplet
                    //
                    //------------------------------------------------------------------
                    x.load(xx);
                    f.load(ff);
                    assert(x.isIncreasing());
                    assert(f.isLocalMinimum());
                }
                else
                {
                    const size_t top = nn-3;
                    if(org>=top)
                    {
                        //--------------------------------------------------------------
                        //
                        // take right-most triplet
                        //
                        //--------------------------------------------------------------
                        x.load(xx+top);
                        f.load(ff+top);
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                    else
                    {
                        //--------------------------------------------------------------
                        //
                        // got at least one point at each side: take closest
                        //
                        //--------------------------------------------------------------
                        assert(org>0);
                        assert(org<top);
                        const size_t lo = org-1;
                        const size_t up = org+3; assert(up<nn);
                        const T      dl = Max(xx[org]-xx[lo],  zero);
                        const T      dr = Max(xx[up]-xx[up-1], zero);
                        if(dl<=dr)
                        {
                            // take left point
                            x.load(xx+lo);
                            f.load(ff+lo);
                            assert(x.isIncreasing());
                            assert(f.isLocalMinimum());
                        }
                        else
                        {
                            // take right point
                            x.load(xx+org);
                            f.load(ff+org);
                            assert(x.isIncreasing());
                            assert(f.isLocalMinimum());
                        }
                    }
                }
            }


            inline void balance(XML::Log &xml, Triplet<T> &x, Triplet<T> &f, Function<T,T> &F)
            {
                Y_XML_Element(xml,Balance);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());

                clear();
                x.save(xx),
                f.save(ff);
                nn=3;

                const T ab = Max<T>(x.b-x.a,zero);
                const T bc = Max<T>(x.c-x.b,zero);
                std::cerr << "ab=" << ab << " | bc=" << bc << std::endl;
                switch( Sign::Of(ab,bc) )
                {
                    case Negative: assert(ab<bc);
                        // cut bc
                        sample(xml,Clamp(x.b, x.b + bc * C, x.c),F);
                        break;

                    case Positive: assert(ab>bc);
                        // cut ab
                        sample(xml,Clamp(x.a, x.b - ab * C, x.b),F);
                        break;

                    case __Zero__:
                        // cut both
                        sample(xml,Clamp(x.b, x.b + bc * C, x.c),F);
                        sample(xml,Clamp(x.a, x.b - ab * C, x.b),F);
                        break;
                }

            }



        };
    }

}

#include "y/utest/run.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/core/rand.hpp"
#include "y/string/env/convert.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T> static inline
    T F(T x)
    {
        const T xopt(0.2f);
        const T delta = x - xopt;
        const T dy(0.66f);
        const T fac(0.37f);
        const T arg = dy + fac * delta * delta;
        return Sqrt<T>(arg);
    }

    template <typename T>
    static inline T getX(Random::CoinFlip &ran)
    {
        const float u = ran.uniform<float>();
        return 1.0f - (u+u);
    }

    template <typename T> static inline
    void testQuadratic(Quadratic<T> &Q, Random::CoinFlip &ran)
    {
        const size_t iter = EnvironmentConvert::To<size_t>("ITER",1);
        size_t       count = 0;
        while(true)
        {
            Triplet<T> xx = { getX<T>(ran), getX<T>(ran), getX<T>(ran) }; if( !xx.isOrdered() )     continue;
            Triplet<T> ff = { F(xx.a), F(xx.b), F(xx.c) };                if( !ff.isLocalMinimum()) continue;

            std::cerr << "ini: xx=" << xx << ", ff=" << ff << std::endl;

            bool         verbose = true;
            XML::Log     xml(std::cerr,verbose);

            for(size_t i=1;i<=10;++i)
                Q.step(xml, F<T>, xx, ff);

            //const T xopt = Golden<T>::Find(xml,F<T>,xx,ff);
            //std::cerr << "xopt=" << xopt << ": Fopt=" << ff.b << std::endl;
            if(++count>=iter)
                break;
        }
    }


}

Y_UTEST(min_quadratic)
{
    //Quadratic<double> qd;
    XRealOutput::Mode = XRealOutput::Compact;
    Core::Rand   ran;

    Quadratic<float>  q;
    testQuadratic(q,ran);
}
Y_UDONE()


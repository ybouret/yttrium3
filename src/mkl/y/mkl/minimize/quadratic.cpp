
#include "y/mkl/minimize/quadratic.hpp"

namespace Yttrium
{
    namespace MKL
    {

        QuadraticStep:: QuadraticStep() noexcept
        {
        }

        QuadraticStep:: ~QuadraticStep() noexcept
        {
        }

        bool QuadraticStep:: Trace = false;

    }

}

#include "y/cameo/multiplication.hpp"
#include "y/container/cxx/light-array.hpp"
#include "y/type/destroy.hpp"
#include "y/stream/libc/output.hpp"
#include "y/xml/element.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/core/hsort.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class Quadratic<T>:: Code : public Object
        {
        public:
            static const size_t              NMAX = 8;
            typedef Cameo::Multiplication<T> VMul;
            typedef LightArray<T>            ArrayType;

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

#include "quadratic/step.hxx"

           

            inline void extrapolate(XML::Log      &xml,
                                    Triplet<T>    &x,
                                    Triplet<T>    &f,
                                    Function<T,T> &F)
            {
                Y_XML_Element_Attr(xml,Extrapolate,Y_XML_Attr(x) << Y_XML_Attr(f));
                clear();

                assert(x.isIncreasing());
                assert(f.isLocalMinimum());

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

                extract(xml,x,f);

            }




            size_t   nn;       //!< number of store values
            const T  zero;     //!< Numeric<T>::ZERO>
            const T  C;        //!< Numeric<T>::GOLDEN_C
            const T  one;      //!< Numeric<T>::ONE>
            VMul     vmul;
            T        xx[NMAX]; //!< x values
            T        ff[NMAX]; //!< f value
            unsigned lc;       //!< line color to trace

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
                        loadFZN(x,f,imin-nl,flatZone);
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

            //__________________________________________________________________________
            //
            //
            // Extract new triplet with AT LEAST FOUR exact numeric minima
            //
            //__________________________________________________________________________
            inline
            void loadFZN(Triplet<T>    & x,
                         Triplet<T>    & f,
                         const size_t    org,
                         const size_t    len) noexcept
            {
                assert(len>=4);
                const size_t nt = len-3; // number of triplets

                size_t small = org;
                size_t lower = org;
                size_t upper = org+2;
                T      width = Max(xx[upper]-xx[lower],zero);
                for(size_t t=1;t<nt;++t)
                {
                    const T wtmp = Max(xx[++upper]-xx[++lower],zero);
                    if(wtmp<width)
                    {
                        width = wtmp;
                        small = lower;
                    }
                }

                x.load(xx+small);
                f.load(ff+small);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());

            }


            inline void goldenRatio(XML::Log &xml, Triplet<T> &x, Triplet<T> &f, Function<T,T> &F)
            {
                Y_XML_Element(xml,GoldenRatio);
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
                        Y_XMLog(xml, "[<]");
                        sample(xml,Clamp(x.b, x.b + bc * C, x.c),F);
                        break;

                    case Positive: assert(ab>bc);
                        // cut ab
                        Y_XMLog(xml, "[>]");
                        sample(xml,Clamp(x.a, x.b - ab * C, x.b),F);
                        break;

                    case __Zero__:
                        // cut both
                        Y_XMLog(xml, "[><]");
                        sample(xml,Clamp(x.b, x.b + bc * C, x.c),F);
                        sample(xml,Clamp(x.a, x.b - ab * C, x.b),F);
                        break;
                }

                extract(xml,x,f);

            }



        };

    }
}


namespace Yttrium
{
    namespace MKL
    {
#define real_t float
#include "quadratic.hxx"
#undef real_t

#define real_t double
#include "quadratic.hxx"
#undef real_t

#define real_t long double
#include "quadratic.hxx"
#undef real_t

#define real_t XReal<float>
#include "quadratic.hxx"
#undef real_t

#define real_t XReal<double>
#include "quadratic.hxx"
#undef real_t

#define real_t XReal<long double>
#include "quadratic.hxx"
#undef real_t

    }

}


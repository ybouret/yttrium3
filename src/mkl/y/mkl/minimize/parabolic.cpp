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
#include "y/mkl/v2d.hpp"
#include <iomanip>

namespace Yttrium
{
    namespace MKL
    {

        ParabolicStep:: ParabolicStep() noexcept
        {
        }

        ParabolicStep:: ~ParabolicStep() noexcept
        {
        }

        bool ParabolicStep:: Trace = false;


        template <typename T>
        class Parabolic<T> :: Code  : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const size_t        NMAX = 8;
            typedef Cameo::Addition<T> XAdd;
            typedef Function<T,T>      FunctionType;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit Code() :
            nn(0),
            one(  Numeric<T>::ONE ),
            zero( Numeric<T>::ZERO ),
            half( Numeric<T>::HALF ),
            C(    Numeric<T>::GOLDEN_C ),
            xx(),
            ff()
            {
            }

            inline virtual ~Code() noexcept {}

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! find better mininum
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
                preload(x,f);


                if(Trace)
                {
                    OutputFile fp("para-func.data");
                    const unsigned np = 10000;
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

                if(Trace)
                {
                    OutputFile fp("para-step.data",true);
                    saveStack(fp,2);
                    saveState(fp,x,f,3);
                }

                //--------------------------------------------------------------
                //
                //
                // balance
                //
                //
                //--------------------------------------------------------------
                balance(xml,x,f,F);

                if(Trace)
                {
                    OutputFile fp("para-step.data",true);
                    saveState(fp,x,f,4);
                }

            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            size_t  nn;        //!< stack size
            const T one;       //!< 1
            const T zero;      //!< 0
            const T half;      //!< 1/2
            const T C;         //!< GOLDEN_C
            T       xx[NMAX];  //!< stack
            T       ff[NMAX];  //!< stack


        private:
            Y_Disable_Copy_And_Assign(Code);

            //! load triplet into stack
            inline void preload(const Triplet<T>    & x,
                                const Triplet<T>    & f) noexcept
            {
                Y_BZero(xx);
                Y_BZero(ff);
                x.save(xx);
                f.save(ff);
                nn = 3;
            }

            static inline void show(XML::Log &xml, const T X, const T FX)
            {
                Y_XMLog(xml, "[+] f(" << X << ") = " << FX );
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


            inline void saveState(OutputStream     & fp,
                                  const Triplet<T> & x,
                                  const Triplet<T> & f,
                                  const unsigned     color) const
            {
                fp("%.15g %.15g %u\n", (double) x[1], (double) f[1], color);
                fp("%.15g %.15g %u\n", (double) x[2], (double) f[2], color);
                fp("%.15g %.15g %u\n", (double) x[3], (double) f[3], color);
                fp("%.15g %.15g %u\n", (double) x[1], (double) f[1], color);
                fp << "\n";
            }

            inline void saveStack(OutputStream &fp, const unsigned color) const
            {
                for(size_t i=0;i<nn;++i)
                {
                    fp("%.15g %.15g %u\n", (double) xx[i], (double) ff[i], color);
                }
                fp("%.15g %.15g %u\n", (double) xx[0], (double) ff[0], color);
                fp << "\n";
            }


            //__________________________________________________________________
            //
            //
            //! best effort to add point(s) towards parabolic approximation
            //
            //__________________________________________________________________
            inline void grow(XML::Log      & xml,
                             Triplet<T>    & x,
                             Triplet<T>    & f,
                             FunctionType  & F)
            {
                Y_XML_Element_Attr(xml,Grow,Y_XML_Attr(x) << Y_XML_Attr(f));
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());

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
                        const T        omb   = Clamp(zero,one-beta,one);
                        const T        alpha = f.a-f.b;
                        const T        gamma = f.c-f.b;

                        switch(Sign::Of(alpha,gamma))
                        {
                            case __Zero__:
                                Y_XMLog(xml, "[alpha=gamma]" );
                                sample(xml,Clamp(x.a,x.a+half*width,x.c),F); // middle
                                break;

                            case Negative: {
                                assert(alpha<gamma);
                                Y_XMLog(xml, "[alpha<gamma]" );
                                const T eta = alpha/gamma;
                                const T u_m = Clamp(zero,half*(one-beta*omb*(one-eta)/(beta+omb*eta)),one);
                                sample(xml,Clamp(x.a,x.a+u_m*(x.c-x.a),x.c),F); // towards x.a
                            } break;

                            case Positive: {
                                Y_XMLog(xml, "[alpha>gamma]");
                                const T eta = gamma/alpha;
                                const T u_m = Clamp(zero,half*(one + beta*omb*(one-eta)/(beta*eta+omb)),one);
                                sample(xml,Clamp(x.a,x.a+u_m*(x.c-x.a),x.c),F); // towads x.c
                            } break;


                        }
                    }
                }


                // extract new state
                extract(xml,x,f);
            }

            inline void loadFlatV1(Triplet<T>    &x,
                                   Triplet<T>    &f,
                                   size_t         im) noexcept
            {
                if(0==im)
                {
                    // left
                    x.a = x.b = xx[0];
                    f.a = f.b = ff[0];
                    x.c = xx[1];
                    f.c = ff[1];
                    assert(x.isIncreasing());
                    assert(f.isLocalMinimum());
                }
                else
                {
                    if(nn-1==im)
                    {
                        // right
                        x.b = x.c = xx[im];
                        f.b = f.c = ff[im];
                        --im;
                        x.a  = xx[im];
                        f.a = ff[im];
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                    else
                    {
                        // core
                        --im;
                        x.load(&xx[im]);
                        f.load(&ff[im]);
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                }
            }

            inline void loadFlatV2(Triplet<T>    &x,
                                   Triplet<T>    &f,
                                   size_t         lower) noexcept
            {
                typedef V2D<T> v2d;
                assert(lower<nn-1);

                if(0==lower)
                {
                    // left
                    x.load(xx);
                    f.load(ff);
                    assert(x.isIncreasing());
                    assert(f.isLocalMinimum());
                }
                else
                {
                    if(nn-2==lower)
                    {
                        // right
                        --lower;
                        x.load(&xx[lower]);
                        f.load(&ff[lower]);
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                    else
                    {
                        std::cerr << "v2 in core!" << std::endl;
                        const size_t il    = lower-1; assert(lower>0);
                        const size_t upper = lower+1;
                        const size_t ir    = upper+1; assert(ir<nn);
                        const v2d    vl(xx[lower]-xx[il],ff[il]-ff[lower]);
                        const v2d    vr(xx[ir]-xx[upper],ff[ir]-ff[upper]);
                        const T      dl = vl.mod2();
                        const T      dr = vr.mod2();
                        std::cerr << "vl=" << vl << " @" << dl << std::endl;
                        std::cerr << "vr=" << vr << " @" << dr << std::endl;
                        if(dl<=dr)
                        {
                            // with left point
                            x.load(&xx[il]);
                            f.load(&ff[il]);
                            assert(x.isIncreasing());
                            assert(f.isLocalMinimum());
                        }
                        else
                        {
                            // with right point
                            x.load(&xx[lower]);
                            f.load(&ff[lower]);
                            assert(x.isIncreasing());
                            assert(f.isLocalMinimum());
                        }
                    }
                }


            }

            inline void loadFlatVN(Triplet<T>    &x,
                                   Triplet<T>    &f,
                                   const size_t   imin,
                                   const size_t   same) noexcept
            {
                exit(1);
            }



            inline void extract(XML::Log      &xml,
                                Triplet<T>    &x,
                                Triplet<T>    &f)
            {
                Y_XML_Element_Attr(xml, Extract, Y_XML_Attr(nn) );

                //--------------------------------------------------------------
                //
                // order xx and ff to have local representation
                //
                //--------------------------------------------------------------
                Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);
                if(xml.verbose)
                {
                    Core::Display( xml() << "xx=",xx,nn) << std::endl;
                    Core::Display( xml() << "ff=",ff,nn) << std::endl;
                }

                //--------------------------------------------------------------
                //
                // find minimum interval
                //
                //--------------------------------------------------------------
                size_t imin=0;
                size_t same=1;
                T      fmin = ff[0];
                for(size_t i=1;i<nn;++i)
                {
                    const T ftmp = ff[i];
                    switch( Sign::Of(ftmp,fmin) )
                    {
                        case Negative: imin = i; fmin=ftmp; same=1; continue;
                        case Positive: break;
                        case __Zero__: ++same; continue;
                    }
                    break;
                }

                Y_XMLog(xml,"fmin=" << fmin << " #" << same);

                switch(same)
                {
                    case 0: throw Specific::Exception("Parabolic::Step", "Corrupted");
                    case 1: loadFlatV1(x,f,imin); break;
                    case 2: loadFlatV2(x,f,imin); break;
                    default: assert(same>=3); loadFlatVN(x,f,imin,same); break;
                }

                Y_XMLog(xml, "--> x=" << x << "; f=" << f);

            }


            inline void extractOld(XML::Log      &xml,
                                Triplet<T>    &x,
                                Triplet<T>    &f)
            {
                Y_XML_Element_Attr(xml, Extract, Y_XML_Attr(nn) );

                //--------------------------------------------------------------
                //
                // sort items
                //
                //--------------------------------------------------------------
                assert(nn>=3);
                Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);

                if(xml.verbose)
                {
                    Core::Display( xml() << "xx=",xx,nn) << std::endl;
                    Core::Display( xml() << "ff=",ff,nn) << std::endl;
                }

                //--------------------------------------------------------------
                //
                // locate minimum
                //
                //--------------------------------------------------------------
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
                    //----------------------------------------------------------
                    //
                    // on the left
                    //
                    //----------------------------------------------------------
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
                        //------------------------------------------------------
                        //
                        // on the right
                        //
                        //------------------------------------------------------
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
                        //------------------------------------------------------
                        //
                        // generic
                        //
                        //------------------------------------------------------
                        assert(im>0); assert(im<nn-1);
                        const size_t ia=im-1;
                        x.load(&xx[ia]); assert(x.isIncreasing());
                        f.load(&ff[ia]); assert(f.isLocalMinimum());
                    }
                }

            }

            inline void sampleRight(XML::Log      & xml,
                                    const T         rw,
                                    Triplet<T>    & x,
                                    Function<T,T> & F)
            {
                sample(xml, Clamp(x.b,x.b + C*rw, x.c), F);
            }

            inline void sampleLeft(XML::Log      & xml,
                                   const T         lw,
                                   Triplet<T>    & x,
                                   Function<T,T> & F)
            {
                sample(xml, Clamp(x.a,x.b - C*lw, x.b), F);
            }

            inline void balance(XML::Log      & xml,
                                Triplet<T>    & x,
                                Triplet<T>    & f,
                                Function<T,T> & F)
            {
                Y_XML_Element(xml,Balance);
                assert(x.isOrdered());
                assert(f.isLocalMinimum());

                //--------------------------------------------------------------
                //
                //
                // initialize length
                //
                //--------------------------------------------------------------
                T lw   = Max(x.b-x.a,zero);
                T rw   = Max(x.c-x.b,zero);
                while(true)
                {
                    //----------------------------------------------------------
                    //
                    // load current state
                    //
                    //----------------------------------------------------------
                    preload(x,f);
                    switch( Sign::Of(lw,rw) )
                    {
                        case Negative: assert(lw<rw);           sampleRight(xml,rw,x,F); break;
                        case Positive: assert(lw>rw);           sampleLeft(xml,lw,x,F);  break;
                        case __Zero__: sampleRight(xml,rw,x,F); sampleLeft(xml,lw,x,F);  break;
                    }
                    extract(xml,x,f);
                    T  wmin = (lw = Max(x.b-x.a,zero));
                    T  wmax = (rw = Max(x.c-x.b,zero));
                    if(wmin>wmax) Swap(wmin,wmax);

                    assert(wmin<=wmax);
                    std::cerr << "wmin=" << wmin << ", wmax=" << wmax << std::endl;
                    if(wmax<=wmin+wmin)
                        break;
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

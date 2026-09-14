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

#include "parabolic/extract.hxx"
#include "parabolic/grow.hxx"
#include "parabolic/balance.hxx"

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
                       // std::cerr << "v2 in core!" << std::endl;
                        const size_t il    = lower-1; assert(lower>0);
                        const size_t upper = lower+1;
                        const size_t ir    = upper+1; assert(ir<nn);
                        const v2d    vl(xx[lower]-xx[il],ff[il]-ff[lower]);
                        const v2d    vr(xx[ir]-xx[upper],ff[ir]-ff[upper]);
                        const T      dl = vl.mod2();
                        const T      dr = vr.mod2();
                        //std::cerr << "vl=" << vl << " @" << dl << std::endl;
                        //std::cerr << "vr=" << vr << " @" << dr << std::endl;
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
                assert(same>=4);
                assert(nn>=4);
                const size_t nt = same-2;          // number of triplets
                size_t       im = imin;            // initial index
                T            wm = xx[im+2]-xx[im]; // initial width

                //std::cerr << "width[0]=" << wm << std::endl;
                for(size_t j=1,i=imin+1;j<nt;++j,++i)
                {
                    const T w = xx[i+2]-xx[i];
                    //std::cerr << "width[" << j << "]=" << w << std::endl;

                    if(w<wm) {
                        im = i;
                        wm = w;
                    }
                }

                //std::cerr << "winner=" << wm << " @" << im << std::endl;
                x.load(&xx[im]); assert(x.isOrdered());
                f.load(&ff[im]); assert(f.isLocalMinimum());
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

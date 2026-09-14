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
                    fp( "%.15g %.15g %u\n", (double) xx[i], (double) ff[i], color);
                fp(     "%.15g %.15g %u\n", (double) xx[0], (double) ff[0], color);
                fp << "\n";
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


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
                      const size_t     pn)
            {
                for(size_t i=0;i<pn;++i)
                {
                    fp("%.15g %.15g\n",(double)px[i], (double)py[i]);
                }
                fp("%.15g %.15g\n",(double)px[0], (double)py[0]);
                fp << "\n";
            }

            inline void saveSample(OutputStream &fp)
            {
                sortSample();
                Save(fp,xx,ff,nn);
            }

            inline void saveTriple(OutputStream &fp, const Triplet<T> &x, const Triplet<T> &f) const
            {
                Save(fp, &x[1], &f[1], 3);
            }


#include "quadratic/step.hxx"
#include "quadratic/find.hxx"

            


            size_t   nn;       //!< number of store values
            const T  zero;     //!< Numeric<T>::ZERO>
            const T  C;        //!< Numeric<T>::GOLDEN_C
            const T  one;      //!< Numeric<T>::ONE>
            VMul     vmul;
            T        xx[NMAX]; //!< x values
            T        ff[NMAX]; //!< f value

        private:
            Y_Disable_Copy_And_Assign(Code);

            inline void sortSample() noexcept {
                Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);
            }

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

#include "quadratic/extrapolate.hxx"
#include "quadratic/goldenratio.hxx"
#include "quadratic/extract.hxx"





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


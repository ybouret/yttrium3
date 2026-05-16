#include "y/cameo/add/scalar.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"


#include "y/calculus/alignment.hpp"
#include "y/type/destruct.hpp"
#include "y/hide.hpp"


namespace Yttrium
{
    namespace Cameo
    {

        template <typename T, typename VECT>
        class VectorialSummator : public Summator<VECT>
        {
        public:
            static const size_t        Dimension = sizeof(VECT)/sizeof(T);
            typedef ScalarSummator<T>  XAddition;
            static const size_t        Requested = Dimension*sizeof(XAddition);
            Y_Args_Declare(VECT,Type);
            Y_Args_Expose(T,Scalar);

            inline VectorialSummator() :
            xadd(0), wksp(), xnum(0)
            {
                init();
            }

            inline virtual ~VectorialSummator() noexcept { quit(); }

            inline friend std::ostream & operator<<(std::ostream &os, const VectorialSummator &self)
            {
                os << '{' << std::endl;
                for(size_t i=0;i<Dimension;++i)
                    os << '\t' << self.xadd[i] << std::endl;
                return os << '}';
            }

            inline virtual void ldz() noexcept {
                for(size_t i=0;i<Dimension;++i) xadd[i].ldz();
            }

            inline virtual void add(ParamType v)
            {
                ConstScalar * const scal = Hide::Cast<Scalar>(&v);
                try {
                    for(size_t i=0;i<Dimension;++i) xadd[i].add(scal[i]);
                }
                catch(...) { ldz(); throw; }
            }

            inline virtual Type operator()(void)
            {
                MutableType v;
                try
                {
                    MutableScalar * const scal = Hide::Cast<Scalar>(&v);
                    for(size_t i=0;i<Dimension;++i) scal[i] = xadd[i]();
                }
                catch(...) { ldz(); throw; }
                ldz();
                return v;
            }

            virtual const char * callSign() const noexcept { return "Cameo::VectorialSummator"; }

        private:
            Y_Disable_Assign(VectorialSummator);
            XAddition * const xadd;
            void *            wksp[ Alignment::WordsGEQ<Requested>::Count ];
            size_t            xnum;

            inline void init()
            {
                assert(0==xadd);
                Coerce(xadd) = static_cast<XAddition*>( Y_BZero(wksp) );
                try
                {
                    while(xnum<Dimension)
                    {
                        new (xadd+xnum) XAddition();
                        ++xnum;
                    }
                }
                catch(...)
                {
                    quit(); throw;
                }
            }
            inline void quit() noexcept
            {
                assert(xadd);
                while(xnum>0) Destruct( &xadd[--xnum] );
                Coerce(xadd) = 0;
                Y_BZero(wksp);
            }
        };

    }
}

#include "y/mkl/complex.hpp"

using namespace Yttrium;

Y_UTEST(cameo_add_scalar)
{
    Y_SIZEOF(Cameo::ScalarSummator<apq>);
    Y_SIZEOF(Cameo::ScalarSummator<int>);
    Y_SIZEOF(Cameo::ScalarSummator<uint32_t>);
    Y_SIZEOF(Cameo::ScalarSummator<float>);
    Y_SIZEOF(Cameo::ScalarSummator< XReal<double> >);


    { Cameo::ScalarSummator<apq>      s; std::cerr << s.callSign() << std::endl; }
    { Cameo::ScalarSummator<int>      s; std::cerr << s.callSign() << std::endl; }
    { Cameo::ScalarSummator<uint32_t> s; std::cerr << s.callSign() << std::endl; }
    { Cameo::ScalarSummator<float>    s; std::cerr << s.callSign() << std::endl; }

    {
        Cameo::VectorialSummator<float,Complex<float> > cs;
        cs << Complex<float>(-1.2,1.3);
        cs << Complex<float>(0.01,-0.82);

        std::cerr << cs << std::endl;
        std::cerr << cs() << std::endl;

    }

}

Y_UDONE()

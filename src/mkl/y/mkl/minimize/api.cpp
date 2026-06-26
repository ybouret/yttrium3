
#include "y/mkl/minimize/api.hpp"
#include "y/mkl/minimize/parabolic.hpp"
#include "y/mkl/minimize/bracket.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class Minimize:: Engine<T> :: Code :
        public Object, public Parabolic<T>
        {
        public:
            using Parabolic<T>::step;

            inline explicit Code() : Object(), Parabolic<T>()
            {

            }
            
            inline virtual ~Code() noexcept
            {
            }

            inline T find(XML::Log          & xml,
                          const Process       how,
                          Triplet<T>        & x,
                          Triplet<T>        & f,
                          Function<T,T>     & F,
                          const Criterion     win)
            {
                Y_XML_Element_Attr(xml,Minimize,Y_XML_Attr(x) << Y_XML_Attr(f));

                switch(how)
                {
                    case Minimize::Direct:
                        assert(f.isLocalMinimum());
                        break;

                    case Minimize::Inside:
                        if(!Bracket::Inside(xml,x,f,F))
                        {
                            (void) F(x.a);
                            return x.a;
                        }
                        assert(f.isLocalMinimum());
                        break;

                    case Minimize::Expand:
                        std::cerr << "Not Implemented" << std::endl;
                        exit(1);
                        break;
                }


                unsigned cycle = 1;
                // initialize
                Y_XMLog(xml, "[cycle=" << cycle << "] [initialize]");
                step(xml,x,f,F);
                T x_opt = x.b;

                // llop
                while(true)
                {
                    ++cycle;
                    Y_XMLog(xml, "[cycle=" << cycle << "]");
                    step(xml,x,f,F);
                    const T    x_new = x.b;
                    const bool f_cvg = AlmostEqual<T>::Are(f.a,f.b) && AlmostEqual<T>::Are(f.b,f.c);
                    const bool x_cvg = AlmostEqual<T>::Are(x_opt,x_new);
                    Y_XMLog(xml, "[f-convergence: " << f_cvg << "]");
                    Y_XMLog(xml, "[x-convergence: " << x_cvg << "]");

                    switch(win)
                    {
                        case Standard: if(f_cvg) goto WIN;
                            break;

                        case Pedantic: if(x_cvg && f_cvg) goto WIN;
                            break;
                    }

                    x_opt = x_new;
                }

            WIN:
                Y_XMLog(xml,"converged: f(" << x.b << ")=" << f.b);
                f.b=F(x.b);
                return x.b;
            }



        private:
            Y_Disable_Copy_And_Assign(Code);
        };




#define real_t float
#include "api.hxx"
#undef real_t

#define real_t double
#include "api.hxx"
#undef real_t

#define real_t long double
#include "api.hxx"
#undef real_t

#define real_t XReal<float>
#include "api.hxx"
#undef real_t

#define real_t XReal<double>
#include "api.hxx"
#undef real_t

#define real_t XReal<long double>
#include "api.hxx"
#undef real_t

    }

}

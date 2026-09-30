
#include "y/mkl/minimize/api.hpp"
#include "y/mkl/minimize/quadratic.hpp"
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
        class Minimize:: Engine<T> :: Code : public Object, public Quadratic<T>
        {
        public:
            using Quadratic<T>::find;

            inline explicit Code() : Object(), Quadratic<T>()
            {
            }

            inline virtual ~Code() noexcept
            {
            }

            inline T find(XML::Log          & xml,
                          const Process       how,
                          Triplet<T>        & x,
                          Triplet<T>        & f,
                          Function<T,T>     & F)
            {
                Y_XML_Element_Attr(xml,Minimize,Y_XML_Attr(x) << Y_XML_Attr(f));

                switch(how)
                {
                    case Minimize::Direct:
                        assert(x.isOrdered());
                        assert(f.isLocalMinimum());
                        break;

                    case Minimize::Inside:
                        if( !Bracket::Inside(xml,x,f,F) )
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

                return find(xml,x,f,F);
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

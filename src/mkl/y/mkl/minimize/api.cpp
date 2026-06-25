
#include "y/mkl/minimize/api.hpp"
#include "y/mkl/minimize/parabolic.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/mkl/api/almost-equal.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class Minimizer<T> :: Code :
        public Object, public Parabolic<T>
        {
        public:
            using Parabolic<T>::step;
            using Parabolic<T>::verbose;

            inline explicit Code() : Object(), Parabolic<T>()
            {

            }
            
            inline virtual ~Code() noexcept
            {
            }

            inline T find(XML::Log &xml, Triplet<T> &x, Triplet<T> &f, Function<T,T> &F)
            {
                // initialize
                step(xml,x,f,F);
                T x_opt = x.b;
                while(true)
                {
                    step(xml,x,f,F);
                    const T    x_new = x.b;
                    const bool f_cvg = AlmostEqual<T>::Are(f.a,f.b) && AlmostEqual<T>::Are(f.b,f.c);
                    const bool x_cvg = AlmostEqual<T>::Are(x_opt,x_new);
                    
                    if(verbose) {
                        std::cerr << "-- f-convergence : " << f_cvg << std::endl;
                        std::cerr << "-- x-convergence : " << x_cvg << std::endl;
                    }

                    if(x_cvg && f_cvg)
                    {
                        f.b = F(x.b);
                        return x.b;
                    }

                    x_opt = x_new;
                }
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

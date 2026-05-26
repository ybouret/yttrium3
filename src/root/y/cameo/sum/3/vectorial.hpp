//! \file

#ifndef Y_Cameo_Sum3_Vectorial_Included
#define Y_Cameo_Sum3_Vectorial_Included 1

#include "y/cameo/sum/3/scalar.hpp"
#include "y/hide.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum {


            //__________________________________________________________________
            //
            //
            //
            //! Summator of 3 vectorial items
            //
            //
            //__________________________________________________________________
            template <typename T, typename VECT>
            class VectorialThree: public Three<VECT>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const size_t       Dimension = sizeof(VECT)/sizeof(T);                //!< alias
                typedef ScalarThree<T>    XAddition;                                         //!< alias
                Y_Args_Declare(VECT,Type);                                              //!< aliases
                Y_Args_Expose(T,Scal);                                                  //!< aliases

                inline explicit VectorialThree() noexcept : sum3() {}
                inline virtual ~VectorialThree() noexcept {}

                inline virtual Type operator()(ParamType a, ParamType b, ParamType c)
                {
                    MutableType v;
                    {
                        ConstScal   * const A = Hide::Cast<ConstScal>(&a);
                        ConstScal   * const B = Hide::Cast<ConstScal>(&b);
                        ConstScal   * const C = Hide::Cast<ConstScal>(&c);
                        MutableScal * const V = Hide::Cast<MutableScal>(&v);
                        for(size_t i=0;i<Dimension;++i)
                            V[i] = sum3(A[i],B[i],C[i]);
                    }
                    return v;
                }

            private:
                Y_Disable_Copy_And_Assign(VectorialThree);
                XAddition sum3;
            };

        }

    }

}

#endif // !Y_Cameo_Sum3_Vectorial_Included


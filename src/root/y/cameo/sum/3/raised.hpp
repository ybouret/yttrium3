

//! \file

#ifndef Y_Cameo_Sum_Raised3_Included
#define Y_Cameo_Sum_Raised3_Included 1

#include "y/cameo/sum/3.hpp"
#include "y/cameo/sum/api/raised.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        namespace Sum
        {
            template <typename T>
            class Raised3 : public Three<T>
            {
            public:
                Y_Args_Declare(T,Type);
                typedef typename ByRaisedAPI<MutableType>::Type Accumulator; //!< alias

                inline explicit Raised3() noexcept : Three<T>() { Y_Cameo_Sum_Raised_Check(); }
                inline virtual ~Raised3() noexcept              {}

                inline virtual Type operator()(ParamType a, ParamType b, ParamType c)
                {
                    Accumulator acc = a;
                    acc += b;
                    acc += c;
                    return acc.template cast<MutableType>(0,0);
                }



            private:
                Y_Disable_Copy_And_Assign(Raised3);
            };
        }

    }

}

#endif // !Y_Cameo_Sum_Raised3_Included




//! \file

#ifndef Y_Cameo_Sum_Queued3_Included
#define Y_Cameo_Sum_Queued3_Included 1

#include "y/cameo/sum/3.hpp"
#include "y/cameo/sum/api/queued.hpp"
#include "y/core/sort3.hpp"
#include "y/mkl/api/fabs.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        namespace Sum
        {
            template <typename T>
            class Queued3 : public Three<T>
            {
            public:
                Y_Args_Declare(T,Type);

                inline explicit Queued3() noexcept : Three<T>() { Y_Cameo_Sum_Queued_Check(); }
                inline virtual ~Queued3() noexcept              {}

                inline virtual Type operator()(ParamType a, ParamType b, ParamType c)
                {
                    MutableType rank[3] = {
                        MKL::Fabs<MutableType>(a),
                        MKL::Fabs<MutableType>(b),
                        MKL::Fabs<MutableType>(c)
                    };
                    MutableType data[3] = { a,b,c };
                    Core::Sort3(rank,data);
                    return (data[0]+data[1]) + data[2];
                }
                
            private:
                Y_Disable_Copy_And_Assign(Queued3);
            };
        }

    }

}

#endif // !Y_Cameo_Sum_Queued3_Included

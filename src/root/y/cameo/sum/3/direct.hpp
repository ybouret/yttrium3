
//! \file

#ifndef Y_Cameo_Sum_Direct3_Included
#define Y_Cameo_Sum_Direct3_Included 1

#include "y/cameo/sum/3.hpp"
#include "y/cameo/sum/api/direct.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        namespace Sum
        {
            //__________________________________________________________________
            //
            //
            //
            //! Direct sum of 3 items
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Direct3 : public Three<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Declare(T,Type); //!< aliases

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Direct3() noexcept : Three<T>() { Y_Cameo_Sum_Direct_Check(); } //!< setup
                inline virtual ~Direct3() noexcept              {}                              //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual Type operator()(ParamType a, ParamType b, ParamType c)
                {
                    return a+b+c;
                }


            private:
                Y_Disable_Copy_And_Assign(Direct3); //!< discarded
            };
        }

    }

}

#endif // !Y_Cameo_Sum_Direct3_Included

//! \file

#ifndef Y_Cameo_Sum_3_Included
#define Y_Cameo_Sum_3_Included 1

#include "y/type/args.hpp"

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
            //! Sum3 interface
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Three
            {
            public:
                Y_Args_Declare(T,Type);
                inline explicit Three() noexcept {}
                inline virtual ~Three() noexcept {}

                virtual Type operator()(ParamType,ParamType,ParamType) = 0;

            private:
                Y_Disable_Copy_And_Assign(Three);
            };
        }
        
    }
}

#endif // !Y_Cameo_Sum_3_Included


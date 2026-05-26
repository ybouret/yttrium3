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
                inline explicit Three() noexcept {} //!< setup
                inline virtual ~Three() noexcept {} //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! \return sum of three items
                virtual Type operator()(ParamType,ParamType,ParamType) = 0;

            private:
                Y_Disable_Copy_And_Assign(Three); //!< discarded
            };
        }
        
    }
}

#endif // !Y_Cameo_Sum_3_Included


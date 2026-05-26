//! \file

#ifndef Y_Cameo_Sum3_Included
#define Y_Cameo_Sum3_Included 1

#include "y/cameo/sum/3/operating.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum {

            template <typename T,const unsigned strategy> struct Selected3;

            //! select Direct
            template <typename T> struct Selected3<T,0>
            {
                typedef Direct3<T> API; //!<alias
            };

            //! select Raised
            template <typename T> struct Selected3<T,1>
            {
                typedef Raised3<T> API; //!< alias
            };

            //! select Queued
            template <typename T> struct Selected3<T,2>
            {
                typedef Queued3<T> API; //!< alias
            };
        }

        //__________________________________________________________________
        //
        //
        //
        //! Performing summation of 3 items
        //
        //
        //__________________________________________________________________
        template <typename T>
        class Sum3 : public Sum::OperatingThree<T>::Type
        {
        public:
            inline explicit Sum3() noexcept {} //!< setup
            inline virtual ~Sum3() noexcept {} //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(Sum3); //!< discarded
        };

    }

}

#endif // !Y_Cameo_Sum3_Included


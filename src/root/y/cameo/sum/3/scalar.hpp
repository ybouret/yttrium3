
//! \file

#ifndef Y_Cameo_Sum3_Scalar_Included
#define Y_Cameo_Sum3_Scalar_Included 1

#include "y/cameo/sum/strategy.hpp"
#include "y/cameo/sum/3/queued.hpp"
#include "y/cameo/sum/3/raised.hpp"
#include "y/cameo/sum/3/direct.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum {

            template <typename T,const unsigned strategy> struct SelectedScalar3;

            //! select Direct
            template <typename T> struct SelectedScalar3<T,0>
            {
                typedef Direct3<T> API; //!<alias
            };

            //! select Raised
            template <typename T> struct SelectedScalar3<T,1>
            {
                typedef Raised3<T> API; //!< alias
            };

            //! select Queued
            template <typename T> struct SelectedScalar3<T,2>
            {
                typedef Queued3<T> API; //!< alias
            };


            //__________________________________________________________________
            //
            //
            //
            //! Performing summation of 3 scalar items
            //
            //
            //__________________________________________________________________
            template <typename T>
            class ScalarThree : public  SelectedScalar3<T,Sum::Strategy<T>::Index>::API
            {
            public:
                inline explicit ScalarThree() noexcept {} //!< setup
                inline virtual ~ScalarThree() noexcept {} //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(ScalarThree); //!< discarded
            };

        }
    }
}


#endif // !Y_Cameo_Sum3_Scalar_Included


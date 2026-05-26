//! \file

#ifndef Y_Cameo_Scalar_Summator_Included
#define Y_Cameo_Scalar_Summator_Included 1

#include "y/cameo/sum/strategy.hpp"
#include "y/cameo/sum/direct.hpp"
#include "y/cameo/sum/raised.hpp"
#include "y/cameo/sum/queued.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        namespace Sum
        {


            template <typename T,const unsigned strategy> struct SelectedScalar;

            //! select Direct
            template <typename T> struct SelectedScalar<T,0>
            {
                typedef Direct<T> API; //!<alias
            };

            //! select Raised
            template <typename T> struct SelectedScalar<T,1>
            {
                typedef Raised<T> API; //!< alias
            };

            //! select Queued
            template <typename T> struct SelectedScalar<T,2>
            {
                typedef Queued<T> API; //!< alias
            };

            //__________________________________________________________________
            //
            //
            //
            //! Scalar summator for a given type
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Scalar : public SelectedScalar<T,Strategy<T>::Index>::API
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                //! alias
                typedef typename SelectedScalar<T,Strategy<T>::Index>::API SummatorType;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Scalar() : SummatorType()                                    {} //!< setup
                inline explicit Scalar(const size_t minCapacity) : SummatorType(minCapacity) {} //!< setup \param minCapacity compatibility
                inline Scalar(const Scalar &other) : SummatorType(other)                     {} //!< duplicate \param other another Scalar
                inline virtual ~Scalar() noexcept                                            {} //!< cleanup
                
            private:
                Y_Disable_Assign(Scalar); //!< discarded
            };


        }


    }

}

#endif // !Y_Cameo_Scalar_Summator_Included


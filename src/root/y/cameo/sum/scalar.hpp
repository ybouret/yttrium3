
//! \file

#ifndef Y_Cameo_Scalar_Summator_Included
#define Y_Cameo_Scalar_Summator_Included 1


#include "y/cameo/sum/direct.hpp"
#include "y/cameo/sum/raised.hpp"
#include "y/cameo/sum/queued.hpp"
#include "y/calculus/integer-log2.hpp"

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
            //! Find out compute strategy
            //
            //
            //__________________________________________________________________
            template <typename T>
            struct Strategy
            {
                Y_Args_Expose(T,Type); //!< aliases
                static const unsigned UseDirect = ByDirectAPI<MutableType>::IsProper ? 0x01 : 0x00; //!< flag
                static const unsigned UseRaised = ByRaisedAPI<MutableType>::IsProper ? 0x02 : 0x00; //!< flag
                static const unsigned UseQueued = ByQueuedAPI<MutableType>::IsProper ? 0x04 : 0x00; //!< flag
                static const unsigned UseResult = UseDirect | UseRaised | UseQueued;                //!< selection flag
                static const unsigned Index     = IntegerLog2<UseResult>::Value;                    //!< selection index
            };

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


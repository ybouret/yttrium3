
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

            template <typename T>
            struct Strategy
            {
                Y_Args_Expose(T,Type);
                static const unsigned UseDirect = ByDirectAPI<MutableType>::IsProper ? 0x01 : 0x00;
                static const unsigned UseRaised = ByRaisedAPI<MutableType>::IsProper ? 0x02 : 0x00;
                static const unsigned UseQueued = ByQueuedAPI<MutableType>::IsProper ? 0x04 : 0x00;
                static const unsigned UseResult = UseDirect | UseRaised | UseQueued;
                static const unsigned Index     = IntegerLog2<UseResult>::Value;
            };

            template <typename T,const unsigned strategy> struct SelectedScalar;

            template <typename T> struct SelectedScalar<T,0>
            {
                typedef Direct<T> API;
            };

            template <typename T> struct SelectedScalar<T,1>
            {
                typedef Raised<T> API;
            };

            template <typename T> struct SelectedScalar<T,2>
            {
                typedef Queued<T> API;
            };

            template <typename T>
            class Scalar : public SelectedScalar<T,Strategy<T>::Index>::API
            {
            public:
                typedef typename SelectedScalar<T,Strategy<T>::Index>::API SummatorType;

                inline explicit Scalar() : SummatorType() {}
                inline explicit Scalar(const size_t minCapacity) : SummatorType(minCapacity) {}
                inline virtual ~Scalar() noexcept {}
                inline Scalar(const Scalar &other) : SummatorType(other) {}
                
            private:
                Y_Disable_Assign(Scalar);
            };


        }


    }

}

#endif // !Y_Cameo_Scalar_Summator_Included



//! \file

#ifndef Y_Cameo_Add_Scalar_Included
#define Y_Cameo_Add_Scalar_Included 1


#include "y/cameo/strategy.hpp"
#include "y/cameo/add/straight.hpp"
#include "y/cameo/add/ap-proxy.hpp"
#include "y/cameo/add/fp-queue.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        namespace Pith
        {
            template <typename T, unsigned UUID> struct AddScalar;

            template <typename T>
            struct AddScalar<T,Straight>
            {
                typedef StraightSummator<T> API;
            };

            template <typename T>
            struct AddScalar<T,AP_Proxy>
            {
                typedef AP_ProxySummator<T> API;
            };

            template <typename T>
            struct AddScalar<T,FP_Queue>
            {
                typedef FP_QueueSummator<T> API;
            };

        }

        template <typename T>
        struct AddScalar
        {
            static const unsigned UUID = Selected<T>::UUID;
            typedef typename Pith::AddScalar<T,UUID>::API API;
        };

        template <typename T>
        class ScalarSummator : public AddScalar<T>::API
        {
        public:
            typedef typename AddScalar<T>::API SummatorType;

            inline explicit ScalarSummator() : SummatorType() {}
            inline explicit ScalarSummator(const size_t minCapacity) : SummatorType(minCapacity) {}

            inline virtual ~ScalarSummator() noexcept {}
        private:
            Y_Disable_Assign(ScalarSummator);
        };



    }

}

#endif // !Y_Cameo_Add_Scalar_Included


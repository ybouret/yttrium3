
//! \file

#ifndef Y_Cameo_Add_AP_Proxy_Included
#define Y_Cameo_Add_AP_Proxy_Included 1


#include "y/cameo/summator.hpp"
#include "y/cameo/ap-proxy.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! Summator for SCALAR Cameo::AP_Proxy API
        //
        //
        //______________________________________________________________________
        template <typename T>
        class AP_ProxySummator : public AP_ProxyCommon, public Summator<T>
        {
        public:
            Y_Args_Declare(T,Type);
            typedef typename UseAP_ProxyAPI<MutableType>::Type Accumulator;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            inline explicit AP_ProxySummator() : acc(0)             {  }               //!< setup empty
            inline explicit AP_ProxySummator(const size_t) : acc(0) {  }               //!< setup empty (compatibility version)
            inline virtual ~AP_ProxySummator() noexcept             { acc.ldz(); }     //!< cleanup
            inline AP_ProxySummator(const AP_ProxySummator &other) : acc(other.acc) {} //!< duplicate \param other another summator

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline void ldz() noexcept       { acc.ldz(); }
            inline void add(ConstType &data) { acc += data; }
            inline Type operator()(void)
            {
                ConstType res = acc.template cast<MutableType>(VarName,VarPart);
                acc.ldz();
                return res;
            }

        private:
            Y_Disable_Assign(AP_ProxySummator);
            Accumulator acc;
        };

    }

}

#endif // !Y_Cameo_Add_AP_Proxy_Included

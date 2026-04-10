
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/number.hpp"
#include "y/apex/types.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Natural : public Number
        {
        public:
            static const char * const CallSign; //!< "apn"

            Natural();
            Natural(const natural_t n);
            Natural(const Natural &);
            Natural & operator=(const Natural &);
            virtual ~Natural() noexcept;
            Y_OSTREAM_PROTO(Natural);
            
            virtual const char * callSign() const noexcept;

            Natural & xch(Natural &) noexcept;
            String    toHex()        const;


        private:
            void * const code;
        };
    }

    typedef Apex::Natural apn;

}

#endif // !Y_Apex_Natural_Included


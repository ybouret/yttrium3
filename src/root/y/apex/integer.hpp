
//! \file

#ifndef Y_Apex_Integer_Included
#define Y_Apex_Integer_Included 1

#include "y/apex/natural.hpp"

namespace Yttrium
{
    namespace Apex
    {

        class Integer : public Number
        {
        public:
            static const char * const CallSign;

            Integer();
            Integer(const Integer &);
            Integer(const Natural &);
            Integer(const integer_t);

            Integer & operator=(const Integer &);
            Integer & operator=(const Natural &);
            Integer & operator=(const integer_t) noexcept;

            virtual ~Integer() noexcept;

            virtual const char * callSign() const noexcept;

            Integer & xch( Integer & ) noexcept;

            

            const SignType s;
            const Natural  n;

        private:

        };
    }

    typedef Apex::Integer mpz;

}

#endif // !Y_Apex_Integer_Included


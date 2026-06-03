//! \file

#ifndef Y_Jive_Syntax_Outcome_Included
#define Y_Jive_Syntax_Outcome_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Jive
    {

        namespace Syntax
        {
            enum Result
            {
                Accepted,
                Rejected
            };
            
            enum Sanity
            {
                Fragile,
                Healthy
            };
            
            enum Status
            {
                Running,
                Blocked
            };
            
            
            
            
            
            class Outcome
            {
            public:
                Outcome(const Result, const Sanity, const Status) noexcept;
                Outcome(const Outcome &) noexcept;
                ~Outcome() noexcept;
                
                Result  result;
                Sanity  sanity;
                Status  status;
                
            private:
                Y_Disable_Assign(Outcome);
                
            };
            
        }
    }

}

#endif // !Y_Jive_Syntax_Outcome_Included

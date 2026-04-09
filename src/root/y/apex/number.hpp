//! \file

#ifndef Y_Apex_Number_Included
#define Y_Apex_Number_Included 1

#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Number : public Identifiable
        {
        public:
            explicit Number() noexcept;
            virtual ~Number() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(Number);
        };
    }
}

#endif // !Y_Apex_Number_Included


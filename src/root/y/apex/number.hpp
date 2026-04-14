//! \file

#ifndef Y_Apex_Number_Included
#define Y_Apex_Number_Included 1

#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //
        //! base class for numbers
        //
        //
        //______________________________________________________________________
        class Number : public Identifiable
        {
        public:
            explicit Number() noexcept; //!< setup
            virtual ~Number() noexcept; //!< cleanup

            virtual void ldz() noexcept; //!< set to zero, nothrow
        private:
            Y_Disable_Copy_And_Assign(Number); //!< discarded
        };
    }
}

#endif // !Y_Apex_Number_Included


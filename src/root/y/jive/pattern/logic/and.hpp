//! \file


#ifndef Y_Jive_Logic_And_Included
#define Y_Jive_Logic_And_Included 1

#include "y/jive/pattern/logic/logic.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Logic AND
        //
        //
        //______________________________________________________________________
        class And : public Logic
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('A', 'N', 'D', '_'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit And() noexcept; //!< setup
            virtual ~And() noexcept; //!< cleanup
            And(const And&);         //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

        private:
            Y_Disable_Assign(And); //!< discarde
        };
    }

}

#endif // !Y_Jive_Logic_And_Included


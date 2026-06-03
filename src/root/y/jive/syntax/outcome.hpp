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

            //__________________________________________________________________
            //
            //
            //! Outcome result
            //
            //__________________________________________________________________
            enum Result
            {
                Accepted, //!< accepted rule
                Rejected  //!< rejected rule
            };

            //__________________________________________________________________
            //
            //
            //! Outcome sanity
            //
            //__________________________________________________________________
            enum Sanity
            {
                Fragile, //!< accepted WITHOUT new node
                Healthy  //!< accepted WITH    new node
            };

            //__________________________________________________________________
            //
            //
            //! Outcome sanity
            //
            //__________________________________________________________________
            enum Status
            {
                Running, //!< no end of stream detected
                Blocked  //!< end of stream was detected
            };
            
            
            //__________________________________________________________________
            //
            //
            //
            //! Outcome for accepts(...) in rules
            //
            //
            //__________________________________________________________________
            class Outcome
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Outcome(const Result, const Sanity, const Status) noexcept; //!< setup
                Outcome(const Outcome &)                          noexcept; //!< duplicate
                ~Outcome()                                        noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Result  result; //!< mutable result
                Sanity  sanity; //!< mutable sanity
                Status  status; //!< mutable status

            private:
                Y_Disable_Assign(Outcome); //!< discarded

            };
            
        }
    }

}

#endif // !Y_Jive_Syntax_Outcome_Included

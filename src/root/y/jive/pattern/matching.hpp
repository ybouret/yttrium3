
//! \file

#ifndef Y_Jive_Matching_Included
#define Y_Jive_Matching_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Matching engine for Module
        //
        //
        //______________________________________________________________________
        class Matching : public Token, public Motif
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! matching manner
            enum How
            {
                Exactly, //!< full module must match pattern
                Somehow  //!< partial module must match pattern
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Matching(Pattern * const) noexcept; //!< setup
            virtual ~Matching()                noexcept; //!< setup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool operator()(const How &, Module * const); //!< \return dispatched call
            bool exactly(Module * const); //!< \return true iff full module matches pattern
            bool somehow(Module * const); //!< \return true iff pattern is found in module



        private:
            Y_Disable_Copy_And_Assign(Matching); //!< discarded
        };

    }

}

#endif // !Y_Jive_Matching_Included


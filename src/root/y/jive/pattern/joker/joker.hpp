
//! \file


#ifndef Y_Jive_Joker_Included
#define Y_Jive_Joker_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Joker Pattern interface
        //
        //
        //______________________________________________________________________
        class Joker : public Pattern
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit Joker(const uint32_t, const Motif &) noexcept; //!< setup
            Joker(const Joker &) noexcept;                          //!< duplicate

        public:
            virtual ~Joker() noexcept; //!< cleanup

            virtual void glean(Leading &) const noexcept;
            
            const Motif motif;
        private:
            Y_Disable_Assign(Joker); //!< discarded

        };

    }


}

#endif // !Y_Jive_Joker_Included


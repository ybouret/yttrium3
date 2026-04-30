
//! \file


#ifndef Y_Jive_Logic_Or_Included
#define Y_Jive_Logic_Or_Included 1

#include "y/jive/pattern/logic/logic.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Logic Or
        //
        //
        //______________________________________________________________________
        class Or : public Logic
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('_', 'O', 'R', '_'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Or() noexcept; //!< setup
            virtual ~Or() noexcept; //!< cleanup
            Or(const Or&);          //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern * clone()                   const;
            virtual bool      univocal()       const noexcept; // empty of 1 univocal
            virtual bool      sound()          const noexcept; // all must be sound
            virtual void      glean(Leading &) const noexcept; // from all patterns
            virtual bool      takes(Token&,Source&)     const; 

        private:
            Y_Disable_Assign(Or); //!< discarde
        };
    }

}

#endif // !Y_Jive_Logic_Or_Included




//! \file


#ifndef Y_Jive_Logic_None_Included
#define Y_Jive_Logic_None_Included 1

#include "y/jive/pattern/logic/logic.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Logic None
        //
        //
        //______________________________________________________________________
        class None : public Logic
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('N', 'O', 'N', 'E'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit None() noexcept; //!< setup
            virtual ~None() noexcept; //!< cleanup
            None(const None&);        //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern *     clone()                   const;
            virtual bool          univocal()       const noexcept; // empty of 1 univocal
            virtual bool          sound()          const noexcept; // all must be sound
            virtual void          glean(Leading &) const noexcept; // from all patterns
            virtual bool          takes(Token&,Source&)     const;
            virtual OutputStream &viz(OutputStream &)       const;

        private:
            Y_Disable_Assign(None); //!< discarde
        };
    }

}

#endif // !Y_Jive_Logic_None_Included


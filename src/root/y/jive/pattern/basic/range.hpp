


//! \file

#ifndef Y_Jive_Range_Included
#define Y_Jive_Range_Included 1

#include "y/jive/pattern/basic/one-char.hpp"
#include "y/jive/pattern/within.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Accept a range of characters
        //
        //
        //______________________________________________________________________
        class Range : public OneChar, public Within
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('R','N','G','E'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Range(const uint8_t,const uint8_t) noexcept; //!< setup
            Range(const Within)                noexcept;
            virtual ~Range()                   noexcept; //!< cleanup
            Range(const Range &)               noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern * clone()                   const;
            virtual size_t    serialize(OutputStream &) const;
            virtual void      glean(Leading &) const noexcept;
            virtual bool      univocal()       const noexcept;

            
        private:
            Y_Disable_Assign(Range); //!< discared
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Range_Included


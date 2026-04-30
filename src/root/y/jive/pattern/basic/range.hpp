


//! \file

#ifndef Y_Jive_Range_Included
#define Y_Jive_Range_Included 1

#include "y/jive/pattern/basic/one-char.hpp"

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
        class Range : public OneChar
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
            explicit Range(const uint8_t,const uint8_t) noexcept; //!< setup
            virtual ~Range()                            noexcept; //!< cleanup
            Range(const Range &)                        noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern * clone()                   const;
            virtual size_t    serialize(OutputStream &) const;
            virtual void      glean(Leading &) const noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint8_t lower; //!< lower bound
            const uint8_t upper; //!< upper bound

        private:
            Y_Disable_Assign(Range); //!< discared
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Range_Included


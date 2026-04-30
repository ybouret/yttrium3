//! \file

#ifndef Y_Jive_Excluded_Included
#define Y_Jive_Excluded_Included 1

#include "y/jive/pattern/basic/one-char.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Accepting all but one char
        //
        //
        //______________________________________________________________________

        class Excluded : public OneChar
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('E','X','C','L'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Excluded(const uint8_t) noexcept; //!< setup
            virtual ~Excluded()              noexcept; //!< cleanup
            Excluded(const Excluded &)       noexcept; //!< duplicate

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
            const uint8_t code; //!< char to exclude

        private:
            Y_Disable_Assign(Excluded); //!< discarded
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Excluded_Included


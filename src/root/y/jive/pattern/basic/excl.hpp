//! \file

#ifndef Y_Jive_Excl_Included
#define Y_Jive_Excl_Included 1

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
        class Excl : public OneChar
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
            explicit Excl(const uint8_t) noexcept; //!< setup
            virtual ~Excl()              noexcept; //!< cleanup
            Excl(const Excl &)           noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern *     clone()                   const;
            virtual size_t        serialize(OutputStream &) const;
            virtual void          glean(Leading &) const noexcept;
            virtual bool          univocal()       const noexcept;
            virtual OutputStream &viz(OutputStream &)       const;
            virtual Pattern *     optimized();

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint8_t code; //!< char to exclude

        private:
            Y_Disable_Assign(Excl); //!< discarded
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Excl_Included


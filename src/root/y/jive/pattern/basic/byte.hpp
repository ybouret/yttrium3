

//! \file

#ifndef Y_Jive_Byte_Included
#define Y_Jive_Byte_Included 1

#include "y/jive/pattern/basic/one-char.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Would accept a single defined char
        //
        //
        //______________________________________________________________________
        class Byte : public OneChar
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('B','Y','T','E'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Byte(const uint8_t) noexcept; //!< setup
            virtual ~Byte()              noexcept; //!< cleanup
            Byte(const Byte &)           noexcept; //!< duplicatee

            //__________________________________________________________________
            //
            //
            // C++
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
            const uint8_t code; //!< accepted code

        private:
            Y_Disable_Assign(Byte); //!< discarded
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Byte_Included


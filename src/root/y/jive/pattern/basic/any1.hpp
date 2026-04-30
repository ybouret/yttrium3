
//! \file

#ifndef Y_Jive_Any1_Included
#define Y_Jive_Any1_Included 1

#include "y/jive/pattern/basic/one-char.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Accept any one character
        //
        //
        //______________________________________________________________________
        class Any1 : public OneChar
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('A','N','Y','1'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Any1()    noexcept; //!< setup
            virtual ~Any1()    noexcept; //!< cleanup
            Any1(const Any1 &) noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern * clone()                   const;
            virtual size_t    serialize(OutputStream &) const;
            virtual void      glean(Leading &) const noexcept;

        private:
            Y_Disable_Assign(Any1); //!< discarded
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Any1_Included


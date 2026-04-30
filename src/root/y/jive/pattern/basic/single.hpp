

//! \file

#ifndef Y_Jive_Single_Included
#define Y_Jive_Single_Included 1

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
        class Single : public OneChar
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('S','N','G','L'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Single(const uint8_t) noexcept; //!< setup
            virtual ~Single()              noexcept; //!< cleanup
            Single(const Single &)         noexcept; //!< duplicatee

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            virtual Pattern * clone()                   const;
            virtual size_t    serialize(OutputStream &) const;
            virtual void      glean(Leading &) const noexcept;
            virtual bool      univocal()       const noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint8_t code; //!< accepted code

        private:
            Y_Disable_Assign(Single); //!< discarded
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Single_Included


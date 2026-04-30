
//! \file

#ifndef Y_Jive_OneChar_Included
#define Y_Jive_OneChar_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! One Char accepting pattern interface
        //
        //
        //______________________________________________________________________
        class OneChar : public Pattern
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit OneChar(const uint32_t) noexcept; //!< setup
            OneChar(const OneChar &)         noexcept; //!< duplicate
        public:
            virtual ~OneChar()               noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool sound() const noexcept;
            virtual bool takes(Token&,Source&) const;
            virtual bool found(const uint8_t) const noexcept = 0; //!< \return true iff acceptable unique char

        private:
            Y_Disable_Assign(OneChar); //!< discarded
        };
    }

}

#endif // !Y_Jive_OneChar_Included


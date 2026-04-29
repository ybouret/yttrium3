
//! \file

#ifndef Y_Jive_OneChar_Included
#define Y_Jive_OneChar_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class OneChar : public Pattern
        {
        protected:
            explicit OneChar(const uint32_t) noexcept;
            OneChar(const OneChar &) noexcept;
        public:
            virtual ~OneChar() noexcept;

            virtual bool sound() const noexcept; //!< \return true
            virtual bool takes(Token&,Source&) const;
            virtual bool found(const uint8_t) const noexcept = 0;
            
        private:
            Y_Disable_Assign(OneChar);
        };
    }

}

#endif // !Y_Jive_OneChar_Included




//! \file

#ifndef Y_Jive_Single_Included
#define Y_Jive_Single_Included 1

#include "y/jive/pattern/basic/one-char.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Single : public OneChar
        {
        public:
            static const uint32_t UUID = Y_FOURCC('S','N','G','L');

            explicit Single(const uint8_t) noexcept;
            virtual ~Single()              noexcept;
            Single(const Single &)         noexcept;

            virtual Pattern * clone()                   const;
            virtual size_t    serialize(OutputStream &) const;

            const uint8_t code;

        private:
            Y_Disable_Assign(Single);
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Single_Included


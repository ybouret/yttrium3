//! \file

#ifndef Y_Stream_IO_Chars_Included
#define Y_Stream_IO_Chars_Included 1

#include "y/object/light.hpp"
#include "y/core/list/cxx.hpp"

namespace Yttrium
{
    namespace IO
    {
        class Char : public LightObject
        {
        public:
            typedef CxxList<Char> List;

            Char(const char) noexcept;
            virtual ~Char() noexcept;
            Char(const Char &) noexcept;

            char &       operator*()       noexcept;
            const char & operator*() const noexcept;

        private:
            Y_Disable_Assign(Char); //!< discarded
            char   data;
        public:
            Char * next;
            Char * prev;
        };

        class Chars : public LightObject, public Char::List
        {
        public:
            explicit Chars() noexcept;
            virtual ~Chars() noexcept;
            Chars(const Chars &);

        private:
            Y_Disable_Assign(Chars);
        };


    }

}

#endif // !Y_Stream_IO_Chars_Included


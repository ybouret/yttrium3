

//! \file

#ifndef Y_Core_String_Included
#define Y_Core_String_Included 1

#include "y/object/counted.hpp"
#include "y/ability/legacy-string.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{

    namespace Core
    {
        class CountedLegacyString : public CountedObject, public LegacyString
        {
        public:
            explicit CountedLegacyString() noexcept;
            virtual ~CountedLegacyString() noexcept;

        private:
            Y_Disable_Copy_And_Assign(CountedLegacyString);
        };


        template <typename T>
        class String : public CountedLegacyString
        {
        public:
            class Code;

            String();
            String(const String &);
            String & operator=(const String &);
            virtual ~String() noexcept;

            virtual const char * c_str() const noexcept;


        private:
            Code * code;
        };
    }

}

#endif // !Y_Core_String_Included


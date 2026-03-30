
//! \file

#ifndef Y_ASCII_Base64_Naming_Included
#define Y_ASCII_Base64_Naming_Included

#include "y/ascii/base64/metrics.hpp"
#include "y/ability/legacy-string.hpp"
#include <cstring>

namespace Yttrium
{
    namespace ASCII
    {
        namespace Base64
        {

            struct MakeName
            {
                static void Encode(char * const       name,
                                   const size_t       nchr,
                                   const void * const data,
                                   const size_t       size) noexcept;
            };

            template <typename T>
            class Naming : public LegacyString
            {
            public:
                inline Naming(const T args) noexcept :
                LegacyString(), name()
                {
                    MakeName::Encode(name, sizeof(name), &args, sizeof(T) );
                }

                inline Naming(const Naming &other) noexcept :
                LegacyString(), name()
                {
                    memcpy(name,other.name,sizeof(name));
                }

                inline virtual ~Naming() noexcept
                {

                }

                inline virtual const char * c_str() const noexcept { return name; }

            private:
                Y_Disable_Assign(Naming);
                char name[CharsFor<sizeof(T)>::Value];
            };
        }

    }

}

#endif // !Y_ASCII_Base64_Naming_Included

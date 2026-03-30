
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

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            struct MakeName
            {
                static void Encode(char * const       name,
                                   const size_t       nchr,
                                   const void * const data,
                                   const size_t       size) noexcept;
            };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            //__________________________________________________________________
            //
            //
            //
            //! create a human readable name from anonymous data
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Naming : public LegacyString
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param args to be converted
                inline Naming(const T args) noexcept :
                LegacyString(), name()
                {
                    MakeName::Encode(name, sizeof(name), &args, sizeof(T) );
                }

                //! duplicate \param other another Naming
                inline Naming(const Naming &other) noexcept :
                LegacyString(), name()
                {
                    memcpy(name,other.name,sizeof(name));
                }

                //! cleanup
                inline virtual ~Naming() noexcept {}

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual const char * c_str() const noexcept { return name; }

            private:
                Y_Disable_Assign(Naming);              //!< discarded
                char name[CharsFor<sizeof(T)>::Value]; //!< inner data
            };
        }

    }

    typedef ASCII::Base64::Naming<void*> NamedAddress; //!< alias

}

#endif // !Y_ASCII_Base64_Naming_Included

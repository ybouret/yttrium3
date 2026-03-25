
//! \file

#ifndef Y_XML_Attribute_Included
#define Y_XML_Attribute_Included 1

#include "y/config/setup.hpp"
#include "y/ostream-proto.hpp"
#include <iostream>
#include <cassert>

namespace Yttrium
{
    namespace XML
    {

        class Attribute
        {
        public:
            typedef std::ostream & (*Show)(std::ostream &, const void * const);
            static const char DQUOTE = '"';
            template <typename T> inline
            Attribute(const char * const userName, const T & userArgs) noexcept :
            name(userName), args( &userArgs ), show( ShowAs<T> )
            {
            }

            ~Attribute() noexcept;

            Attribute(const Attribute &) noexcept;

            Y_OSTREAM_PROTO(Attribute);


            const char * const name;
            const void * const args;
            Show         const show;

        private:
            Y_Disable_Assign(Attribute);
            template <typename T> static inline
            std::ostream & ShowAs(std::ostream &os, const void * const data)
            {
                assert(data);
                const T &value = *static_cast<const T *>(data);
                return os << DQUOTE << value << DQUOTE;
            }

        };
    }

}

#define Y_XML_Attr(NAME) Yttrium::XML::Attribute(#NAME,NAME)

#endif // !Y_XML_Attribute_Included

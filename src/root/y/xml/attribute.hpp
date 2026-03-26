
//! \file

#ifndef Y_XML_Attribute_Included
#define Y_XML_Attribute_Included 1

#include "y/config/setup.hpp"
#include "y/ostream-proto.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>

namespace Yttrium
{
    namespace XML
    {

        //______________________________________________________________________
        //
        //
        //
        //! flexible attribute display
        //
        //
        //______________________________________________________________________
        class Attribute
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef std::ostream & (*Show)(std::ostream &,
                                           const void * const,
                                           const unsigned); //!< alias
            static const char DQUOTE = '"';                                     //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param userName PERSISTENT name
             \param userArgs PERSISTENT args
             \param w        optional field width
             */
            template <typename T> inline
            Attribute(const char * const userName, const T & userArgs, const unsigned w=0) noexcept :
            name(userName), args( &userArgs ), show( ShowAs<T> ), wlen(w)
            {
            }


            ~Attribute() noexcept;                 //!< cleanup
            Attribute(const Attribute &) noexcept; //!< duplicate
            Y_OSTREAM_PROTO(Attribute);            //!< display

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const char * const name; //!< name
            const void * const args; //!< address of value
            Show         const show; //!< show value
            const unsigned     wlen; //!< width

        private:
            Y_Disable_Assign(Attribute); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename T> static inline
            std::ostream & ShowAs(std::ostream      & os,
                                  const void * const  data,
                                  const unsigned      width)
            {
                assert(data);
                const T &value = *static_cast<const T *>(data);
                return os << DQUOTE << std::setw(width) << value << DQUOTE;
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }

}

//! helper to display an attribute
#define Y_XML_Attr(NAME) Yttrium::XML::Attribute(#NAME,NAME)

//! helper to display an attribue with width
#define Y_XML_Attr_Setw(NAME,n) Yttrium::XML::Attribute(#NAME,NAME,n)

#endif // !Y_XML_Attribute_Included

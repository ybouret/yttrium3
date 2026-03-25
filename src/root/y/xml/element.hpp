//! \file

#ifndef Y_XML_Element_Included
#define Y_XML_Element_Included 1

#include "y/xml/log.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{
    namespace XML
    {

        class Element
        {
        public:
            static const char LANGLE = '<';
            static const char RANGLE = '>';
            static const char SLASH  = '/';

            explicit Element(Log               & userOut,
                             const char * const  userTag,
                             const bool          userOne = false);
            virtual ~Element() noexcept;

            Element & operator<<(const Attribute attr);

            void end();

            Log  &             out; //!< output
            const char * const tag; //!< tag
            const bool         one; //!< standalone flag

        private:
            Y_Disable_Copy_And_Assign(Element);
        };
        
    }
}




#endif // !Y_XML_Element_Included


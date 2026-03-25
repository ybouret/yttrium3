//! \file

#ifndef Y_XML_Element_Included
#define Y_XML_Element_Included 1

#include "y/xml/log.hpp"

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

            explicit Element(const char * const  userTag,
                             Log               & userOut,
                             const bool          userOne = false,
                             const bool          userAtr = false) noexcept;
            virtual ~Element() noexcept;

            std::ostream & prolog(); //!< open \return out() << '<' + tag
            void           epilog(); //!< *out << '>' << std::endl

            const char * const tag;
            Log  &             out;
            const bool         one;
            const bool         atr;

        private:
            Y_Disable_Copy_And_Assign(Element);
        };
        
    }
}

#endif // !Y_XML_Element_Included


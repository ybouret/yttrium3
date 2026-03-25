//! \file

#ifndef Y_XML_Element_Included
#define Y_XML_Element_Included 1

#include "y/xml/log.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{
    namespace XML
    {
        //______________________________________________________________________
        //
        //
        //
        //! Element to display on XML::Log
        //
        //
        //______________________________________________________________________
        class Element
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char LANGLE = '<'; //!< alias
            static const char RANGLE = '>'; //!< alias
            static const char SLASH  = '/'; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param userOut PERSISTENT XML::Log
             \param userTag PERSISTENT tag
             \param userOne standalone flag
             */
            explicit Element(Log               & userOut,
                             const char * const  userTag,
                             const bool          userOne = false);

            //! cleanup
            virtual ~Element() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! display attribute in out \param attr attribute \return *this
            Element & operator<<(const Attribute attr);

            //! display required end of tag
            void end();

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

            Log  &             out; //!< output
            const char * const tag; //!< tag
            const bool         one; //!< standalone flag

        private:
            Y_Disable_Copy_And_Assign(Element); //!< discarded
        };
        
    }
}

//! helper for element with no attributes
#define Y_XML_Element(xml,NAME) \
/**/ Yttrium::XML::Element NAME(xml,#NAME); NAME.end()

//! helper for standalone element with attribute(s)
#define Y_XML_Standalone(xml,NAME,ATTR)\
/**/    do { \
/**/        Yttrium::XML::Element NAME(xml,#NAME,true); NAME << ATTR; NAME.end(); \
/**/     } while(false)

//! helper for element with attribute(s)
#define Y_XML_Element_Attr(xml,NAME,ATTR) \
/**/ Yttrium::XML::Element NAME(xml,#NAME); NAME << ATTR; NAME.end()

#endif // !Y_XML_Element_Included


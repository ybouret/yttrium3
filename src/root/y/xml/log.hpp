
//! \file

#ifndef Y_XML_Log_Included
#define Y_XML_Log_Included 1

#include "y/config/setup.hpp"
#include <iosfwd>

namespace Yttrium
{
    namespace XML
    {
        //______________________________________________________________________
        //
        //
        //
        //! Proxy to display Elements
        //
        //
        //______________________________________________________________________
        class Log
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param output output stream \param verbosity PERSISTENT verbosity
            explicit Log(std::ostream &output,
                         bool &        verbosity) noexcept;

            virtual ~Log() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            std::ostream & operator()(void) noexcept; //!< indented output \return os with level indent
            std::ostream & operator*()      noexcept; //!< raw output      \return os

            //! indent stream \return stream
            static std::ostream & Indent(std::ostream &, const size_t);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            std::ostream & os;      //!< PERSISTENT output
            bool         & verbose; //!< PERSISTENT verbose
            size_t         level;   //!< current indentation level

        private:
            Y_Disable_Copy_And_Assign(Log); //!< discarded
        };
    }

}

//! conditional print of a message
#define Y_XMLog(xml,MSG) do { if(xml.verbose) { xml() << MSG << std::endl; } } while(false)

#endif // !Y_XML_Log_Included


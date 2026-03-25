
//! \file

#ifndef Y_XML_Log_Included
#define Y_XML_Log_Included 1

#include "y/config/setup.hpp"
#include <iosfwd>

namespace Yttrium
{
    namespace XML
    {
        class Log
        {
        public:
            explicit Log(std::ostream &output,
                         bool &        verbosity) noexcept;

            virtual ~Log() noexcept;

            std::ostream & operator()(void) noexcept; //!< indented output \return os with level indent
            std::ostream & operator*()      noexcept; //!< raw output      \return os

            static std::ostream & Indent(std::ostream &, const size_t);

            std::ostream & os;
            bool &         verbose;
            size_t         level;

        private:
            Y_Disable_Copy_And_Assign(Log);
        };
    }

}

#endif // !Y_XML_Log_Included


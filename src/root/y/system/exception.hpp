
//! \file

#ifndef Y_System_Exception_Included
#define Y_System_Exception_Included 1

#include "y/exception.hpp"
#include "y/system/error.hpp"
#include "y/libc/str/fmt.h"
#include <cassert>

namespace Yttrium
{


    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! Exception based on Error
        //
        //
        //______________________________________________________________________
        template <typename ERROR_API>
        class LegacyException : public Specific::Exception
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename ERROR_API::Type ErrorType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! initialize
            /**
             \param errorCode    from ERROR
             \param formatString printf-like format string
             */
            explicit LegacyException(const ErrorType    errorCode,
                                     const char* const  formatString,
                                     ...) noexcept Y_Printf_Check(3, 4);


            //! duplicate
            /** \param other source */
            inline LegacyException(const LegacyException& other) noexcept :
            Specific::Exception(other),
            code(other.code)
            {
            }

            //! cleanup
            inline virtual ~LegacyException() noexcept {}

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const ErrorType code; //!< keep track or error code

        private:
            Y_Disable_Assign(LegacyException); //!< discarding
        };

        template <typename ERROR_API>
        inline LegacyException<ERROR_API>::LegacyException(const typename ERROR_API::Type err,
                                                           const char* const         formatString,
                                                           ...) noexcept :
        Specific::Exception(),
        code(err)
        {
            assert(0 != formatString);
            {
                va_list ap;
                va_start(ap, formatString);
                (void)Yttrium_Strfmt(info_, sizeof(info_), formatString, &ap);
                va_end(ap);
            }
            ERROR_API::Format(what_, sizeof(what_), code);
        }
    }

    namespace Libc
    {
        typedef Core::LegacyException<Libc::Error> Exception; //!< alias
    }

    namespace Windows
    {
        typedef Core::LegacyException<Windows::Error> Exception; //!< alias
    }

#if defined(Y_Darwin)
    namespace Mach
    {
        typedef Core::LegacyException<Mach::Error> Exception; //!< alias
    }
#endif // defined(Y_Darwin)

    namespace System
    {
#if defined(Y_BSD)
        typedef Libc::Exception Exception;
#endif

#if defined(Y_WIN)
        typedef Windows::Exception Exception;
#endif
    }




}

#endif // !Y_System_Exception_Included


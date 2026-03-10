//! \file

#ifndef Y_Exception_Included
#define Y_Exception_Included 1

#include "y/config/setup.hpp"
#include "y/check/printf.h"
#include <exception>
#include <iosfwd>


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Contextual exception
    //
    //
    //__________________________________________________________________________
    class Exception : public std::exception
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const size_t       InfoLength = 256; //!< internal length for what
        static const char * const CallSign;         //!< "Exception"
        
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Exception()                           noexcept;
        explicit Exception(const char * const fmt,...) noexcept Y_Printf_Check(2,3);
        virtual ~Exception()         noexcept; //!< cleanup
        Exception(const Exception &) noexcept; //!< duplicate

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const char * what() const noexcept; //!< exception nature \return CallSign

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        const char * info() const noexcept; //!< provides information \return info_
        void display(std::ostream &) const;

        Exception & operator<<(const char * const) noexcept;
        Exception & operator>>(const char * const) noexcept;

        Exception & cat(const char * const fmt, ...) noexcept Y_Printf_Check(2,3);
        Exception & pre(const char * const fmt, ...) noexcept Y_Printf_Check(2,3);
        
        

    private:
        Y_Disable_Assign(Exception); //!< discard
    protected:
        char info_[InfoLength];      //!< information
    };


    namespace Specific
    {
        class Exception : public Yttrium::Exception
        {
        public:
            static const size_t WhatLength = 128;
            Exception(const char * const nature, const char * const fmt, ...) noexcept Y_Printf_Check(3,4);
            Exception(const Exception &) noexcept;
            virtual ~Exception() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * what() const noexcept; //!< specific reason \return what_

        private:
            Y_Disable_Assign(Exception);
            char what_[WhatLength];
        };
    }


}

#endif // !Y_Exception_Included



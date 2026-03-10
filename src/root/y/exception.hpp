//! \file

#ifndef Y_Exception_Included
#define Y_Exception_Included 1

#include "y/config/setup.hpp"
#include <exception>

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
        static const size_t       WhenLength = 128; //!< internal length for when
        static const size_t       WhatLength = 256; //!< internal length for what
        static const char * const CallSign;         //!< "Exception"
        
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Exception()         noexcept; //!< setup
        virtual ~Exception()         noexcept; //!< cleanup
        Exception(const Exception &) noexcept; //!< duplicate

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const char * what() const noexcept; //!< what cause exception \return what_

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        const char *         when() const noexcept; //!< context of exception \return when_

    private:
        Y_Disable_Assign(Exception); //!< discard
        void ldz() noexcept;         //!< cleanup
        char when_[WhenLength];      //!< when data
        char what_[WhatLength];      //!< what data
    };
}

#endif // !Y_Exception_Included



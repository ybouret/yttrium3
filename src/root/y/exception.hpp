//! \file

#ifndef Y_Exception_Included
#define Y_Exception_Included 1

#include "y/config/setup.hpp"
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
        explicit Exception()         noexcept; //!< setup
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

    private:
        Y_Disable_Assign(Exception); //!< discard
        char info_[InfoLength];      //!< information
    };


    namespace Specific
    {
        class Exception : public Yttrium::Exception
        {
        public:
            static const size_t WhatLength = 128;

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



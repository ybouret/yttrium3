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
        static const size_t       WhatLength = 128; //!< internal bytes
        static const size_t       InfoLength = 256; //!< internal length for what
        static const char * const CallSign;         //!< "Exception"
        
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup for formatted info \param fmt format string
        explicit Exception(const char * const fmt,...) noexcept Y_Printf_Check(2,3);
        explicit Exception()                           noexcept; //!< setup empty
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
        void display(std::ostream &) const; //!< pretty display


        Exception & operator<<(const char * const) noexcept; //!< right append text \return *this
        Exception & operator>>(const char * const) noexcept; //!< left append text \return *this

        //! right append formatted info \param fmt format string \return *this
        Exception & cat(const char * const fmt, ...) noexcept Y_Printf_Check(2,3);

        //! left append formatted info \param fmt format string \return *this
        Exception & pre(const char * const fmt, ...) noexcept Y_Printf_Check(2,3);

        //! append optional 'for varName.varPart'
        /**
         \param varName optional varName
         \param varPart optional varPart, used iff varName != 0
         \return *this
         */
        Exception & signedFor(const char * const varName, const char * const varPart) noexcept;



    private:
        Y_Disable_Assign(Exception); //!< discarded
        void init() noexcept;
        
    protected:
        char what_[WhatLength];      //!< nature
        char info_[InfoLength];      //!< information
    };


    namespace Specific
    {
        //______________________________________________________________________
        //
        //
        //
        //! Exception with nature and info
        //
        //
        //______________________________________________________________________
        class Exception : public Yttrium::Exception
        {
        public:

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param nature explanation \param fmt format string
            Exception(const char * const nature, const char * const fmt, ...) noexcept Y_Printf_Check(3,4);
            Exception(const Exception &) noexcept; //!< duplicate
            virtual ~Exception()         noexcept; //!< cleanup


        private:
            Y_Disable_Assign(Exception); //!< discarded
                                         //!
        protected:
            Exception()   noexcept; //!< setup empty
        };
    }


}

#endif // !Y_Exception_Included



//! \file

#ifndef Y_Stream_IO_Chars_Included
#define Y_Stream_IO_Chars_Included 1

#include "y/object/light.hpp"
#include "y/core/list/cxx.hpp"

namespace Yttrium
{
    namespace IO
    {
        //______________________________________________________________________
        //
        //
        //
        //! lightweight dynamic char for I/O
        //
        //
        //______________________________________________________________________
        class Char : public LightObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxList<Char> List; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Char(const char)   noexcept; //!< setup
            Char(const Char &) noexcept; //!< duplicate
            virtual ~Char()    noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            char &       operator*()       noexcept; //!< access \return data
            const char & operator*() const noexcept; //!< access, const \return data

        private:
            Y_Disable_Assign(Char); //!< discarded
            char   data;            //!< inner data
        public:
            Char * next; //!< for list
            Char * prev; //!< for list
        };

        //______________________________________________________________________
        //
        //
        //
        //! Used as I/O buffer
        //
        //
        //______________________________________________________________________
        class Chars : public LightObject, public Char::List
        {
        public:
            explicit Chars() noexcept; //!< setup
            virtual ~Chars() noexcept; //!< cleanup
            Chars(const Chars &);      //!< duplicate content

        private:
            Y_Disable_Assign(Chars); //!< discarde
        };


    }

}

#endif // !Y_Stream_IO_Chars_Included


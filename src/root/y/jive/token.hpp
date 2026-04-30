
//! \file

#ifndef Y_Jive_Token_Included
#define Y_Jive_Token_Included 1

#include "y/jive/char.hpp"
#include "y/core/list/cxx.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! List of Chars
        //
        //
        //______________________________________________________________________
        class Token : public CxxList<Char>
        {
        public:
            explicit Token() noexcept; //!< setup
            virtual ~Token() noexcept; //!< cleanup
            Token(const Token &);      //!< duplicate
            Y_OSTREAM_PROTO(Token);    //!< display as string

            Token & operator<<(Char * const) noexcept; //!< merge tail \return *this
            Token & operator>>(Char * const) noexcept; //!< merge head \return *this

            String toString() const; //!< \return human readable string

        private:
            Y_Disable_Assign(Token); //!< discarded
        };

    }

}

#endif // !Y_Jive_Token_Included


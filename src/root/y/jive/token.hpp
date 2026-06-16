
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
        class Token : public CxxListOf<Char>
        {
        public:
            explicit Token() noexcept; //!< setup
            virtual ~Token() noexcept; //!< cleanup
            Token(const Token &);      //!< duplicate
            Y_OSTREAM_PROTO(Token);    //!< display as string

            Token & operator<<(Char * const) noexcept; //!< merge tail \return *this
            Token & operator>>(Char * const) noexcept; //!< merge head \return *this

            //! convert token to string
            /**
             \param skip character(s) to skip
             \param trim character(s) to trim
             \return human readable string
             */
            String str(const size_t skip=0,const size_t trim=0) const;

            //! convert token to raw string
            /**
             \param skip character(s) to skip
             \param trim character(s) to trim
             \return raw string
             */
            String raw(const size_t skip=0,const size_t trim=0) const;



            static bool AreEqual(const Token &, const Token &)   noexcept; //!< \return equality test
            friend bool operator==(const Token &, const Token &) noexcept; //!< \return true iff equal
            friend bool operator!=(const Token &, const Token &) noexcept; //!< \return true iff different


        private:
            Y_Disable_Assign(Token); //!< discarded
        };

    }

}

#endif // !Y_Jive_Token_Included


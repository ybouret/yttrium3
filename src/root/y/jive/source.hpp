
//! \file

#ifndef Y_Jive_Source_Included
#define Y_Jive_Source_Included 1

#include "y/jive/module.hpp"
#include "y/jive/token.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Bufferized, Smart pointer to Module
        //
        //
        //______________________________________________________________________
        class Source : public InputStream
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Source(Module * const) noexcept; //!< setup
            virtual ~Source()               noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Char *       get();                         //!< \return character, NULL on EOF
            void         unget(Char * const)  noexcept; //!< unget read character
            void         unget(Token &)       noexcept; //!< unget read token
            void         uncpy(const Token &);          //!< unget of copy of token
            void         skip(size_t)   noexcept;       //!< skip chars from buffer
            size_t       cached() const noexcept;       //!< \return buff.size
            const Char * peek();                        //!< \return NULL if EOF
            void         endl() noexcept;               //!< signal new line
            void         fetch(size_t);                 //!< prefetch if possible

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool   query(char &);
            virtual void   store(const char);
            virtual size_t query(void * const, const size_t);

        private:
            Y_Disable_Copy_And_Assign(Source); //!< discarded
            Module * const impl;               //!< inner module
            Token          buff;               //!< inner buffer
        };

    }

}
#endif // !Y_Jive_Source_Included

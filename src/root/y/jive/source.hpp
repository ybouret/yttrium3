
//! \file

#ifndef Y_Jive_Source_Included
#define Y_Jive_Source_Included 1

#include "y/jive/module.hpp"
#include "y/jive/token.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Source : public InputStream
        {
        public:
            explicit Source(Module * const) noexcept;
            virtual ~Source()               noexcept;

            Char *       get();
            void         unget(Char * const)  noexcept;
            void         unget(Token &)       noexcept;
            void         uncpy(const Token &);
            void         skip(size_t) noexcept;
            size_t       cached() const noexcept; //!< \return buff.size
            const Char * peek();
            void         endl() noexcept;
            void         fetch(size_t);

            virtual bool   query(char &);
            virtual void   store(const char);
            virtual size_t query(void * const, const size_t);

        private:
            Y_Disable_Copy_And_Assign(Source);
            Module * const impl;
            Token          buff;
        };

    }

}
#endif // !Y_Jive_Source_Included

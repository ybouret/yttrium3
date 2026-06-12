//! \file

#ifndef Y_Chemical_Formula_Included
#define Y_Chemical_Formula_Included 1

#include "y/jive/syntax/xnode.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Jive::Syntax::XNode XNode;
        typedef Jive::Syntax::XList XList;

        class Formula_ : public CountedObject
        {
        public:
            static Formula_ * Create(XNode * const);
            virtual          ~Formula_() noexcept;

            XNode * const code;

        private:
            Y_Disable_Copy_And_Assign(Formula_);
            explicit Formula_(XNode * const) noexcept;
        };

        class Formula : public ArcPtr<Formula_>
        {
        public:
            static const char * const CallSign;
            class Translator;

            explicit Formula(XNode * const);
            explicit Formula(const Formula &) noexcept;
            virtual ~Formula() noexcept;

            String makeName(int * const = 0) const;
            String makeHTML() const;
            
        private:
            Y_Disable_Assign(Formula);
        };

    }
}

#endif // !Y_Chemical_Formula_Included


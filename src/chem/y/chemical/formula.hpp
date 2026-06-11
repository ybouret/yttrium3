//! \file

#ifndef Y_Chemical_Formula_Included
#define Y_Chemical_Formula_Included 1

#include "y/jive/syntax/xnode.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef Jive::Syntax::XNode XNode;

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
            explicit Formula(XNode * const);
            explicit Formula(const Formula &) noexcept;
            virtual ~Formula() noexcept;

        private:
            Y_Disable_Assign(Formula);
        };

    }
}

#endif // !Y_Chemical_Formula_Included


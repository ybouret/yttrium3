
//! \file

#ifndef Y_Jive_Matching_Included
#define Y_Jive_Matching_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Matching : public Token, public Motif
        {
        public:
            enum How
            {
                Exactly,
                Somehow
            };

            explicit Matching(Pattern * const) noexcept;
            virtual ~Matching() noexcept;

            bool operator()(const How &, Module * const);

            bool exactly(Module * const);
            bool somehow(Module * const);



        private:
            Y_Disable_Copy_And_Assign(Matching);
        };

    }

}

#endif // !Y_Jive_Matching_Included


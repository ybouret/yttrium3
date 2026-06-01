
//! \file

#ifndef Y_Jive_Syntax_Compound_Included
#define Y_Jive_Syntax_Compound_Included 1

#include "y/jive/syntax/rule/internal.hpp"
#include "y/handy/basic/light/list.hpp"
//#include "y/type/proxy.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            typedef Handy::BasicLightList<const Rule> RList;
            typedef RList::NodeType                   RNode;


            class Compound : public Internal, public RList
            {
            public:
                template <typename ID>
                explicit Compound(const ID      & ruleName,
                                  const uint32_t  ruleUUID) :
                Internal(ruleName,ruleUUID)
                {
                }

                
                virtual ~Compound() noexcept;

                Compound & operator<<(const Rule &);
                virtual OutputStream & vizLink(OutputStream &) const;


            private:
                Y_Disable_Copy_And_Assign(Compound);

            };

        }

    }

}

#endif // !Y_Jive_Syntax_Compound_Included

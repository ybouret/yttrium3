//! \file

#ifndef Y_Jive_Syntax_XNode_Included
#define Y_Jive_Syntax_XNode_Included 1

#include "y/jive/syntax/xlist.hpp"
#include "y/jive/syntax/defs.hpp"
#include "y/pointer/auto.hpp"
#include "y/object/light.hpp"
#include "y/core/meta-max.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            typedef LightObject XObject;

            class XNode : public XObject
            {
            public:
                typedef AutoPtr<Lexeme> LxPtr;
                static const size_t     NumBytes = MetaMax<sizeof(LxPtr),sizeof(XList)>::Value;
                static const size_t     NumWords = Alignment::WordsGEQ<NumBytes>::Count;

                explicit XNode(const Identifier &) noexcept;
                explicit XNode(Lexeme * const)      noexcept;
                virtual ~XNode() noexcept;

                Lexeme       & lexeme()                  noexcept;
                const Lexeme & lexeme()            const noexcept;
                const char *   humanReadableKind() const noexcept;
                XList        & list()                    noexcept;
                const XList  & list()              const noexcept;

                void returnTo(Lexical::Stack &stack) noexcept;


                const Identifier name;
                const Kind       kind;
                XNode *          next;
                XNode *          prev;

            private:
                Y_Disable_Copy_And_Assign(XNode);
                void * const     addr;
                void *           wksp[ NumWords ];
                
            };
        }

    }

}

#endif // !Y_Jive_Syntax_XNode_Included


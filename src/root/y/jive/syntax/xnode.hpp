//! \file

#ifndef Y_Jive_Syntax_XNode_Included
#define Y_Jive_Syntax_XNode_Included 1

#include "y/jive/syntax/xlist.hpp"
#include "y/jive/syntax/rule.hpp"
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
            typedef LightObject XObject; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! XNode for AST
            //
            //
            //__________________________________________________________________
            class XNode : public XObject
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef AutoPtr<Lexeme> LxPtr;                                                  //!< alias
                static const size_t     NumBytes = MetaMax<sizeof(LxPtr),sizeof(XList)>::Value; //!< variant bytes
                static const size_t     NumWords = Alignment::WordsGEQ<NumBytes>::Count;        //!< for workspace

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit XNode(const Rule &)                 noexcept; //!< new internal node
                explicit XNode(const Rule &, Lexeme * const) noexcept; //!< new terminal node
                virtual ~XNode()                             noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________


                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                Lexeme       & lexeme()                  noexcept; //!< \return lexeme for terminal node
                const Lexeme & lexeme()            const noexcept; //!< \return lexeme for terminal node (const)
                XList        & list()                    noexcept; //!< \return list   for internal node
                const XList  & list()              const noexcept; //!< \return list   for internal node (const
                void returnTo(Lexical::Stack &)          noexcept; //!< return to lexer using its stack

                static void Grow(XNode * &tree, XNode * const node) noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Rule  & rule; //!< creating rule
                XNode *       next; //!< for xlist
                XNode *       prev; //!< for xlist

            private:
                Y_Disable_Copy_And_Assign(XNode);  //!< discarded
                void * const  addr;             //!< inner address
                void *        wksp[ NumWords ]; //!< inner workspace

            };
        }

    }

}

#endif // !Y_Jive_Syntax_XNode_Included


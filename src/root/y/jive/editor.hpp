
//! \file

#ifndef Y_Jive_Editor_Included
#define Y_Jive_Editor_Included 1

#include "y/jive/syntax/xnode.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Editor
        {
        public:
            class Code;
            typedef Functor<void,TL1(Token &)> OnTerminal;
            typedef Functor<void,TL1(size_t)>  OnInternal;
            typedef Syntax::XNode              XNode; //!< echo

            explicit Editor(const Identifier &);
            virtual ~Editor() noexcept;

            template <typename ID, typename OBJECT_POINTER, typename METHOD_POINTER> inline
            void on(const ID &id, OBJECT_POINTER const host, METHOD_POINTER const meth)
            {
                const Identifier name(id);
                const OnTerminal proc(host,meth);
                attach(name,proc);
            }

            template <typename ID, typename OBJECT_POINTER, typename METHOD_POINTER> inline
            void cb(const ID &id, OBJECT_POINTER const host, METHOD_POINTER const meth)
            {
                const Identifier name(id);
                const OnInternal proc(host,meth);
                attach(name,proc);
            }

            void operator()(const AutoPtr<XNode> &) const;



        private:
            Y_Disable_Copy_And_Assign(Editor);
            Code * const code;
            void attach(const Identifier &, const OnInternal &);
            void attach(const Identifier &, const OnTerminal &);
        public:
            bool & verbose;
        };

    }

}

#endif // !Y_Jive_Editor_Included


//! \file

#ifndef Y_Jive_Editor_Included
#define Y_Jive_Editor_Included 1

#include "y/jive/syntax/xnode.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Jive
    {
        enum EditPolicy
        {
            Rigorous,
            Tolerant
        };

        //______________________________________________________________________
        //
        //
        //
        //! Editor to convert AST into data
        //
        //
        //______________________________________________________________________
        class Editor
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class Code;
            typedef Jive::Lexeme                      Lexeme;
            typedef Functor<void,TL1(const Lexeme &)> OnTerminal; //!< alias
            typedef Functor<void,TL1(size_t)>         OnInternal; //!< alias
            typedef Syntax::XNode                     XNode;      //!< echo

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Editor(const Identifier &); //!< setup
            virtual ~Editor() noexcept;         //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void initialize();

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            template <typename ID, typename OBJECT_POINTER, typename METHOD_POINTER> inline
            void on(const ID &id, OBJECT_POINTER const host, METHOD_POINTER const meth)
            {
                const String     name(id);
                const OnTerminal proc(host,meth);
                attach(name,proc);
            }

            template <typename ID, typename OBJECT_POINTER, typename METHOD_POINTER> inline
            void cb(const ID &id, OBJECT_POINTER const host, METHOD_POINTER const meth)
            {
                const String     name(id);
                const OnInternal proc(host,meth);
                attach(name,proc);
            }

            void operator()(const AutoPtr<XNode> &, const EditPolicy = Rigorous);
            void operator()(const XNode * const, const EditPolicy = Rigorous);


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        private:
            Y_Disable_Copy_And_Assign(Editor);
            Code * const code;
            void attach(const String &, const OnInternal &);
            void attach(const String &, const OnTerminal &);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        public:
            const size_t     &depth;   //!< inner depth
            const Identifier  lang;    //!< processed grammar
            bool &            verbose; //!< inner verbosity
        };


#define Y_Jive_OnTerminal(CLASS,NAME) on(#NAME,this, & CLASS:: on##NAME)
#define Y_Jive_OnInternal(CLASS,NAME) cb(#NAME,this, & CLASS:: on##NAME)

    }

}

#endif // !Y_Jive_Editor_Included


//! \file

#ifndef Y_Jive_Editor_Included
#define Y_Jive_Editor_Included 1

#include "y/jive/syntax/xnode.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //! Policy while editing
        //
        //______________________________________________________________________
        enum EditPolicy
        {
            Rigorous, //!< each met internal/terminal must have a callback
            Tolerant  //!< edit whatever
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
            typedef Jive::Lexeme                      Lexeme;     //!< echo
            typedef Functor<void,TL1(const Lexeme &)> OnTerminal; //!< callback alias
            typedef Functor<void,TL1(size_t)>         OnInternal; //!< callback alias
            typedef Syntax::XNode                     XNode;      //!< echo

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Editor(const Identifier &); //!< setup
            virtual ~Editor() noexcept;          //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void initialize();  //!< initialize before editing

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! create call for terminal
            /**
             \param id terminal id
             \param host object
             \param meth object method
             */
            template <typename ID, typename OBJECT_POINTER, typename METHOD_POINTER> inline
            void on(const ID &id, OBJECT_POINTER const host, METHOD_POINTER const meth)
            {
                const String     name(id);
                const OnTerminal proc(host,meth);
                attach(name,proc);
            }

            //! create call for internal
            /**
             \param id internal id
             \param host object
             \param meth object method
             */
            template <typename ID, typename OBJECT_POINTER, typename METHOD_POINTER> inline
            void cb(const ID &id, OBJECT_POINTER const host, METHOD_POINTER const meth)
            {
                const String     name(id);
                const OnInternal proc(host,meth);
                attach(name,proc);
            }

            void operator()(const XNode * const,    const EditPolicy = Rigorous); //!< edition process
            void operator()(const AutoPtr<XNode> &, const EditPolicy = Rigorous); //!< edition process


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


#define Y_Jive_OnTerminal(CLASS,NAME) on(#NAME,this, & CLASS:: on##NAME) //!< helper
#define Y_Jive_OnInternal(CLASS,NAME) cb(#NAME,this, & CLASS:: on##NAME) //!< helper

    }

}

#endif // !Y_Jive_Editor_Included

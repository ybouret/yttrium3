#include "y/jive/editor.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/exception.hpp"
#include "y/core/indent.hpp"
#include "y/jive/syntax/rule.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    namespace Jive
    {


#define Y_Jive_Editor(PFX,MSG) do { if(verbose) { Core::Indent(std::cerr << PFX << ' ', (depth<<1), '.') << MSG << std::endl; } } while(false)

        class Editor:: Code : public Object
        {
        public:
            template <typename FUNCTOR>
            class Article : public CountedObject
            {
            public:
                typedef Keyed<String,ArcPtr<Article>> Pointer;

                inline explicit Article(const String &itemName, const FUNCTOR &itemProc) :
                CountedObject(),
                name(itemName),
                proc(itemProc)
                {
                }

                inline virtual ~Article() noexcept
                {
                }


                inline const String & key() const noexcept { return name; }

                const String    name;
                mutable FUNCTOR proc;
            private:
                Y_Disable_Copy_And_Assign(Article);
            };

            typedef Article<OnTerminal>                      TerminalArticle;
            typedef Article<OnInternal>                      InternalArticle;
            typedef HashSet<String,TerminalArticle::Pointer> TDB;
            typedef HashSet<String,InternalArticle::Pointer> IDB;

            inline explicit Code(const Identifier &userLang) :
            Object(),
            lang(userLang),
            tdb(),
            idb(),
            policy(Rigorous),
            verbose(false)
            {
            }

            inline virtual ~Code() noexcept
            {
            }

            inline void on(const String &name, const OnTerminal &proc)
            {
                attach(name,proc,tdb);
            }

            inline void on(const String &name, const OnInternal &proc)
            {
                attach(name,proc,idb);
            }

            inline void run(const XNode * const root)
            {
                assert(root);
                depth = 0;
                walk(root);
            }


            size_t           depth;
            const Identifier lang;
            TDB              tdb;
            IDB              idb;
            EditPolicy       policy;
            bool             verbose;

        private:
            Y_Disable_Copy_And_Assign(Code);
            template <typename FUNCTOR, typename DATABASE>
            void attach(const String     &name,
                        const FUNCTOR    &proc,
                        DATABASE         &db)
            {
                const typename Article<FUNCTOR>::Pointer article = new Article<FUNCTOR>(name,proc);
                if(!db.insert(article))
                    throw Specific::Exception(lang->c_str(),"multiple '%s'", name.c_str());
            }


            inline void walk(const XNode * const node)
            {
                static const char    tpfx[] = "[push]";
                static const char    ipfx[] = "[call]";
                const Syntax::Rule & rule = node->rule;
                const String       & name = *rule.name;

                if(node->rule.isTerminal())
                {
                    const Lexeme &lx = node->lexeme();
                    if(lx.size>0)
                        Y_Jive_Editor(tpfx,name << ": '" << lx.str() << "'");
                    else
                        Y_Jive_Editor(tpfx,name);
                    const TerminalArticle::Pointer * const todo = tdb.search( name );
                    if(todo)
                        (**todo).proc(lx);
                    else
                        applyPolicyFor(name);
                }
                else
                {
                    const Syntax::XList & xlist = node->list();
                    const size_t          nargs = xlist.size;
                    ++depth;
                    for(const XNode *child=xlist.head;child;child=child->next)
                        walk(child);
                    --depth;
                    Y_Jive_Editor(ipfx,name<<"/"<<nargs);
                    const InternalArticle::Pointer * const todo = idb.search( name );
                    if(todo)
                        (**todo).proc(nargs);
                    else
                        applyPolicyFor(name);
                }
            }

            inline void applyPolicyFor(const String &name) const
            {
                switch(policy)
                {
                    case Rigorous: throw Specific::Exception(lang->c_str(),"no processing of '%s'",name.c_str());
                    case Tolerant: break;
                }
            }
        };

        Editor:: Editor(const Identifier &userLang) :
        code( new Code(userLang) ),
        depth( code->depth ),
        lang( code->lang ),
        verbose( code->verbose )
        {
        }

        Editor:: ~Editor() noexcept
        {
            Destroy(code);
        }

        void Editor:: attach(const String &name, const OnInternal &proc)
        {
            assert(code);
            code->on(name,proc);
        }

        void Editor:: attach(const String &name, const OnTerminal &proc)
        {
            assert(code);
            code->on(name,proc);
        }


        void Editor:: operator()(const AutoPtr<XNode> &tree,
                                 const EditPolicy      policy)
        {
            assert(tree.isValid());
            (*this)( & *tree, policy);
        }

        void Editor:: operator()(const XNode * const   tree,
                                 const EditPolicy      policy)
        {
            assert(tree);
            assert(code);
            initialize();
            code->policy = policy;
            code->run( tree );
        }

        void Editor:: initialize()
        {
            if(verbose) std::cerr << "[init] " << lang << std::endl;
        }



    }

}


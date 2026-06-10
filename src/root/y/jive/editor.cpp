#include "y/jive/editor.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/exception.hpp"
#include "y/core/indent.hpp"
#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {


#define Y_Jive_Editor(PFX,MSG) do { if(verbose) { Core::Indent(std::cerr << PFX << ' ', (depth<<1), '.') << MSG << std::endl; } } while(false)

        class Editor:: Code : public Object
        {
        public:
            template <typename FUNCTOR>
            class Article : public Identifier
            {
            public:
                inline explicit Article(const Identifier &itemName, const FUNCTOR &itemProc) :
                Identifier(itemName), proc(itemProc)
                {
                }

                inline virtual ~Article() noexcept
                {
                }

                inline Article(const Article &_) : Identifier(_), proc(_.proc) {}

                FUNCTOR proc;
            private:
                Y_Disable_Assign(Article);
            };

            typedef Article<OnTerminal>             TerminalArticle;
            typedef Article<OnInternal>             InternalArticle;
            typedef HashSet<String,TerminalArticle> TDB;
            typedef HashSet<String,InternalArticle> IDB;

            inline explicit Code(const Identifier &userLang) :
            Object(),
            lang(userLang),
            tdb(),
            idb(),
            verbose(false)
            {
            }

            inline virtual ~Code() noexcept
            {
            }

            inline void on(const Identifier &name, const OnTerminal &proc)
            {
                attach(name,proc,tdb);
            }

            inline void on(const Identifier &name, const OnInternal &proc)
            {
                attach(name,proc,idb);
            }

            inline void walk(const XNode * const root) const
            {
                assert(root);
                walk(root,0);
            }


            const Identifier lang;
            TDB              tdb;
            IDB              idb;
            bool             verbose;

        private:
            Y_Disable_Copy_And_Assign(Code);
            template <typename FUNCTOR, typename DATABASE>
            void attach(const Identifier &name,
                        const FUNCTOR    &proc,
                        DATABASE         &db)
            {
                const Article<FUNCTOR> article(name,proc);
                if(!db.insert(article))
                    throw Specific::Exception(lang->c_str(),"multiple '%s'", name->c_str());
            }


            inline void walk(const XNode * const node, size_t depth) const
            {
                static const char    tpfx[] = "[push]";
                static const char    ipfx[] = "[call]";
                const Syntax::Rule & rule = node->rule;
                const String       & name = *rule.name;
                if(node->rule.isTerminal())
                {
                    const Lexeme &lx = node->lexeme();
                    if(lx.size>0)
                        Y_Jive_Editor(tpfx,lx.name << ": '" << lx.str() << "'");
                    else
                        Y_Jive_Editor(tpfx,lx.name);
                }
                else
                {
                    const Syntax::XList & xlist = node->list();
                    const size_t          nargs = xlist.size;
                    ++depth;
                    for(const XNode *child=xlist.head;child;child=child->next)
                        walk(child,depth);
                    --depth;
                    Y_Jive_Editor(ipfx,name<<"/"<<nargs);

                }
            }
        };

        Editor:: Editor(const Identifier &userLang) :
        code( new Code(userLang) ),
        verbose( code->verbose )
        {
        }

        Editor:: ~Editor() noexcept
        {
            Destroy(code);
        }

        void Editor:: attach(const Identifier &name, const OnInternal &proc)
        {
            assert(code);
            code->on(name,proc);
        }

        void Editor:: attach(const Identifier &name, const OnTerminal &proc)
        {
            assert(code);
            code->on(name,proc);
        }


        void Editor:: operator()(const AutoPtr<XNode> &tree) const
        {
            assert(tree.isValid());
            assert(code);
            code->walk( & *tree );
        }


    }

}


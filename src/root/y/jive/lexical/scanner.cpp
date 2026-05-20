
#include "y/jive/lexical/scanner.hpp"
#include "y/jive/lexical/scanner/meta-table.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            class Scanner:: Code : public Object
            {
            public:

                inline explicit Code(const Identifier &sid) :
                name(sid),
                rlist(),
                table(sid)
                {
                    std::cerr << "sizeof(Scanner::Code) = " << sizeof(Code) << std::endl;
                }


                inline virtual ~Code() noexcept
                {
                }

                inline void add(Rule * const rule)
                {
                    assert(rule);
                    AutoPtr<Rule> guard(rule);
                    std::cerr << "-- adding " << rule->name << " to " << name << std::endl;
                    {
                        const String &rid = *rule->name;
                        for(const Rule *mine=rlist.head;mine;mine=mine->next)
                        {
                            if( rid == *mine->name )
                            {
                                throw Specific::Exception(name->c_str(),"mulitple rule '%s'",rid.c_str());
                            }
                        }
                    }
                    rlist.pushTail( guard.yield() );
                }

                const Identifier name;
                CxxListOf<Rule>  rlist;
                MetaTable        table;

            private:
                Y_Disable_Copy_And_Assign(Code);
            };

            Scanner::Code * Scanner:: CreateCode(const Identifier &sid)
            {
                return new Code(sid);
            }


            Scanner:: ~Scanner() noexcept
            {
                assert(code);
                Destroy(code);
            }

            void Scanner:: add(Rule * const rule)
            {
                assert(rule);
                assert(code);

                code->add(rule);
            }


        }

    }

}



#include "y/jive/lexical/scanner.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"
#include "y/jive/pattern/leading.hpp"
#include "y/type/destruct.hpp"
#include "y/ascii/printable.hpp"
#include "y/handy/basic/light/list.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"
//#include "y/hashing/ibj32.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/container/associative/hash/map.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            namespace
            {
                typedef Handy::BasicLightList<const Rule,SingleThreadedClass> RList;

                class MetaList : public CountedObject, public RList
                {
                public:
                    inline explicit MetaList() noexcept {}
                    inline virtual ~MetaList() noexcept {}
                    
                private:
                    Y_Disable_Copy_And_Assign(MetaList);
                };

                class MetaHasher
                {
                public:
                    inline  MetaHasher() noexcept {}
                    inline ~MetaHasher() noexcept {}

                    inline size_t operator()(const uint8_t &k) const noexcept
                    {
                        return k;
                    }

                private:
                    Y_Disable_Copy_And_Assign(MetaHasher);
                };


                typedef ArcPtr<MetaList>                           SharedMetaList;
                typedef HashMap<uint8_t,SharedMetaList,MetaHasher> MetaMap;

                class MetaTable : public MetaMap
                {
                public:
                    inline explicit MetaTable(const Identifier &sid) :
                    MetaMap(),
                    name(sid)
                    {
                    }

                    inline virtual ~MetaTable() noexcept
                    {
                    }

                    MetaList & operator[](const uint8_t code)
                    {
                        // look for existing
                        {
                            SharedMetaList * const psml = search(code);
                            if(psml) return **psml;
                        }

                        // create new meta list
                        SharedMetaList sml( new MetaList() );
                        if( !insert(code,sml) )
                            throw Specific::Exception(name->c_str(),
                                                      "unexpected table construction failure for '%s'",
                                                      ASCII::Printable::Char[code]);
                        return *sml;
                    }

                    // dispatch rule in (all) matching list(s)
                    void dispatch(const Rule &rule)
                    {
                        MetaTable & table = *this;
                        Leading     lead;

                        rule.form->glean(lead);
                        for(unsigned i=0;i<256;++i)
                        {
                            const uint8_t b = (uint8_t)i;
                            if(!lead.get(b)) continue;
                            table[b] << rule;
                        }
                    }

                    const Identifier name;

                private:
                    Y_Disable_Copy_And_Assign(MetaTable);
                };



            }


            class Scanner:: Code : public Object
            {
            public:

                inline explicit Code(const Identifier &sid) :
                name(sid),
                rlist()
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


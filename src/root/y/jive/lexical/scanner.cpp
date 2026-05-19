
#include "y/jive/lexical/scanner.hpp"
#include "y/calculus/meta2.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"
#include "y/jive/pattern/leading.hpp"
#include "y/type/destruct.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            namespace
            {

                class MetaRule : public Object
                {
                public:
                    inline MetaRule(const Rule &userRule) noexcept :
                    rule(userRule), next(0)
                    {
                    }
                    inline ~MetaRule() noexcept {}

                    const Rule &rule;
                    MetaRule   *next;
                    MetaRule   *prev;
                    
                private:
                    Y_Disable_Copy_And_Assign(MetaRule);
                };

                typedef Core::ListOf<MetaRule> MetaSlot;

                class MetaRules
                {
                public:
                    static const size_t   NumSlots   = 256;
                    static const size_t   BlockBytes = NumSlots * sizeof(MetaSlot);
                    static const unsigned BlockShift = MetaCeilLog2<BlockBytes>::Value;

                    explicit MetaRules() : slot( Acquire() )
                    {
                        for(size_t i=0;i<NumSlots;++i)
                        {
                            new ( slot+i ) MetaSlot();
                        }
                    }

                    inline void dispatch(const Rule &rule)
                    {
                        try
                        {
                            Leading leading;
                            rule.form->glean(leading);
                            for(unsigned i=0;i<256;++i)
                            {
                                const uint8_t b = (uint8_t)i;
                                if( leading.get( b ) )
                                {
                                    std::cerr << "\t '" << rule.name << "' -> '" << ASCII::Printable::Char[b] << "'" << std::endl;
                                    slot[i].pushTail( new MetaRule(rule) );
                                }
                            }
                        }
                        catch(...)
                        {
                            eraseLast(rule);
                            throw;
                        }
                    }

                    inline virtual ~MetaRules() noexcept
                    {
                        static Memory::Archon & archon = Memory::Archon::Location();
                        for(size_t i=0;i<NumSlots;++i)
                        {
                            MetaSlot & sl = slot[i];
                            while(sl.size) delete sl.popTail();
                            Destruct( &sl );
                        }
                        archon.releaseBlock(slot,BlockShift);
                    }


                private:
                    Y_Disable_Copy_And_Assign(MetaRules);
                    MetaSlot * const slot;

                    static inline MetaSlot * Acquire()
                    {
                        static Memory::Archon & archon = Memory::Archon::Instance();
                        return static_cast<MetaSlot*>(archon.acquireBlock(BlockShift));
                    }

                    inline void eraseLast(const Rule &rule) noexcept
                    {
                        for(size_t i=0;i<NumSlots;++i)
                        {
                            MetaSlot &sl = slot[i];
                            if(sl.tail && (&rule == &(sl.tail->rule)) )
                                delete sl.popTail();
                        }
                    }
                };


            }


            class Scanner:: Code : public Object
            {
            public:

                inline explicit Code(const Identifier &sid) :
                name(sid),
                rlist(),
                mlist()
                {
                    std::cerr << "sizeof(Scanner::Code) = " << sizeof(Code) << std::endl;
                    std::cerr << "MetaRules::BlockBytes = " << MetaRules::BlockBytes << std::endl;
                    std::cerr << "MetaRules::BlockShift = " << MetaRules::BlockShift << std::endl;
                    std::cerr << "sizeof(MetaRule)      = " << sizeof(MetaRule) << std::endl;
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
                    mlist.dispatch(*rule);
                    rlist.pushTail( guard.yield() );
                }

                const Identifier name;
                CxxListOf<Rule>  rlist;
                MetaRules        mlist;

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


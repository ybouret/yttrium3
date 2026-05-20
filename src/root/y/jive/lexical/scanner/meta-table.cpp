
#include "y/jive/lexical/scanner/meta-table.hpp"
#include "y/ascii/printable.hpp"
#include "y/exception.hpp"
#include "y/jive/pattern/leading.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            MetaTable:: ~MetaTable() noexcept
            {
            }

            MetaTable:: MetaTable(const Identifier &sid) :
            MetaMap(),
            name(sid)
            {
            }

            MetaList & MetaTable:: operator[](const uint8_t code)
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


            void MetaTable:: dispatch(const Rule &rule)
            {
                try
                {
                    MetaTable & table = *this;
                    Leading     lead;
                    rule.form->glean(lead);
                    for(unsigned i=0;i<256;++i)
                    {
                        const uint8_t code = (uint8_t)i;
                        if(!lead.get(code)) continue;
                        assert( !table[code].found(rule) );
                        table[code] << rule;
                        std::cerr << "\t'" << ASCII::Printable::Char[code] << " => '" << rule.name << "'" << std::endl;
                    }
                }
                catch(...)
                {
                    emergencyRemove(rule);
                    throw;
                }
            }

            void MetaTable:: emergencyRemove(const Rule &rule) noexcept
            {
                for(Iterator it=begin();it!=end();++it)
                {
                    MetaList &L = **it;
                    if(L->tail->isEqualTo(rule))
                    {
                        L.popTail();
                    }
                }
            }


        }
    }
}


#include "y/chemical/weasel/parser.hpp"
#include "y/chemical/reactive/equilibrium/db.hpp"
#include "y/jive/pattern/matching.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/exception.hpp"

#include "y/container/algorithm/crop.hpp"
#include <cctype>
#include <cstring>

namespace Yttrium
{
    namespace Chemical
    {
        void Weasel:: onAlias(const String & expr,
                              Library      & lib,
                              Equilibria   & eqs)
        {
            std::cerr << "process regular expression \"" << expr << "\"" << std::endl;
            Jive::Matching match = expr;
            Vector<size_t> found;
            for(unsigned i=0;i<EDB::Count;++i)
            {
                const char * const txt  = EDB::Table[i]; assert(EDB::Table[i]);
                const char *       ini  = strchr(txt,'@');   if(!ini) throw Specific::Exception(CallSign,"missing '@' for EDB[%u]",i);
                const char * const end  = strchr(ini++,':'); if(!end) throw Specific::Exception(CallSign,"missing ':' for EDB[%u]",i);
                String             eid(ini,(size_t)(end-ini));
                Algorithm::Crop(eid,isspace);
                if( match.found(Jive::Matching::Somehow, eid, eid) )
                    found << i;
            }
            
            if( found.size() <= 0)
                throw Specific::Exception(CallSign,"no matching '%s' in database", expr.c_str());

            for(size_t i=1;i<=found.size();++i)
            {
                
                (*this)( Jive::Module::OpenData(expr,EDB::Table[ found[i]]), lib, eqs);
            }

        }

    }

}

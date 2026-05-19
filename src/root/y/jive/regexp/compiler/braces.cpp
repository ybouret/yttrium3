

#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/ascii/printable.hpp"

#include <cstring>

namespace Yttrium
{

    namespace Jive
    {
        void RXCompiler:: braces(Logic &p)
        {
            assert(curr[-1] == LBRACE);

            const char * const ini = curr;
            while(true)
            {
                if(curr>=last) throw Specific::Exception(CallSign,"missing '%c' in '%s'", RBRACE, expr);
                if(RBRACE == *(curr++)) break;
            }
            const char * const end = curr-1;
            const String       uid(ini,(size_t)(end-ini));
            std::cerr << "uid='" << uid << "'" << std::endl;
            if(uid.size()<=0) throw Specific::Exception(CallSign,"empty braces in sub-expression #%u of '%s'", ixpr, expr);

            if(isalpha(uid[1]))
            {
                if(!dict) throw Specific::Exception(CallSign, "no dictionary for '%s'", uid.c_str());
                Pattern * const q = dict->clone(uid);
                if(!q)    throw Specific::Exception(CallSign, "no pattern '%s' in dictionary'", uid.c_str());
                p << q;
                return;
            }


            throw Specific::Exception(CallSign,"invalid '%s' in braces", ASCII::Printable::Text(uid[1]));

        }
    }

}



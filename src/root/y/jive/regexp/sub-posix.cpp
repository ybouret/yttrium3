
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/posix.hpp"
#include "y/exception.hpp"

namespace Yttrium
{

    namespace Jive
    {
        static inline bool IsPosixEnd(const char * const curr) noexcept
        {
            assert(curr);
            return (':' == curr[0]) && (RXCompiler::RBRACK == curr[1]);
        }

        Pattern * RXCompiler:: subPosix()
        {
            assert(LBRACK == curr[-2]);
            assert(':'    == curr[-1]);
            if(curr>=last) goto UNFINISHED;

            {
                const char * const ini = curr;
                while(curr+1<last)
                {
                    if(!IsPosixEnd(curr)) {++curr; continue;}

                    const String    name(ini,(size_t)(curr-ini));
                    Pattern * const p = posix::named(name);
                    if(!p) throw Specific::Exception(CallSign,"unknown posix '%s' in '%s'",name.c_str(),expr);
                    curr += 2; // skip ':]'
                    return p;
                }
            }

        UNFINISHED:
            throw Specific::Exception(CallSign,"unfinished posix group in '%s'",expr);
        }
    }

}


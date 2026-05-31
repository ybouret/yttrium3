
#include "y/jive/pattern/matching.hpp"
#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Matching:: Matching(Pattern * const p) noexcept :
        Token(),
        Motif(p)
        {

        }

        Matching:: Matching(const String &s) :
        Token(),
        Motif( RegExp::Compile(s,0) )
        {
        }

        Matching:: Matching(const char * const s) :
        Token(),
        Motif( RegExp::Compile(s,0) )
        {
        }

        Matching:: Matching(const Matching &other) :
        Token(other),
        Motif(other)
        {
        }
        

        Matching:: ~Matching() noexcept
        {
        }

        bool Matching:: exactly(Module * const m)
        {
            Token &       token = *this;
            Source        source(m);
            const Motif & motif = *this;
            token.release();
            if(!motif->takes(token,source))
                return false; // no math
            if(source.peek())
                return false; // remaining chars
            return true;
        }

        bool Matching:: somehow(Module * const m)
        {
            bool          result = false;
            Token &       token = *this;
            Source        source(m);
            const Motif & motif = *this;
            token.release();

        TRY:
            assert(0==token.size);
            if( motif->takes(token,source) )
            {
                result = true;
                if(token.size>0)
                    return true;
                // motif may be frail
                assert(motif->frail());
            }
            if(!source.peek())
                return result;
            source.skip(1);
            goto TRY;
        }

        bool Matching:: operator()(const Request how, Module * const m)
        {
            switch(how)
            {
                case Exactly: return exactly(m);
                case Somehow: return somehow(m);
            }

            delete m;
            return false;
        }

    }

}

#include "y/container/associative/suffix/set.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"
#include "y/stream/libc/input.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

namespace
{
    typedef Keyed<String,ArcPtr<String>> SharedString;
    typedef Lexicon<String,SharedString> SLexicon;

    static inline
    void TestLexicon( SLexicon &lexicon, const Readable<String> &words, Core::Rand &ran)
    {
        Vector<String> keys;
        for(size_t i=1;i<=words.size();++i)
        {
            const SharedString s = new String( words[i] );
            if( lexicon.insert(s) ) keys << *s;
        }
        std::cerr << "#keys = " << keys.size() << std::endl;

        Random::Shuffle(ran,keys(),keys.size());
        for(size_t i=keys.size();i>0;--i)
        {
            Y_ASSERT(0!=lexicon.search(keys[i]));
        }
        const size_t nmax = keys.size()/2;
        while(keys.size()>nmax)
        {
            const String key = keys.tail(); keys.popTail();
            Y_ASSERT(lexicon.remove(key));
            Y_ASSERT(!lexicon.remove(key));
        }
    }
}

Y_UTEST(container_lexicon)
{

    Vector<String> words;
    Core::Rand     ran;
    if(argc>1)
    {
        {
            InputFile fp(argv[1]);
            String    line;
            while(fp.gets(line)) words << line;
        }
        std::cerr << "#read = " << words.size() << std::endl;

        SuffixSet<String,SharedString> S;
        HashSet<String,SharedString>   H;

        TestLexicon(S,words,ran); Iter::Test::AllForward(S);
        TestLexicon(H,words,ran); Iter::Test::AllForward(H);

        S.free();
        H.free();
        Iter::Test::AllForward(S);
        Iter::Test::AllForward(H);
    }

}
Y_UDONE()

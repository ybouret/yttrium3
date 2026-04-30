#include "y/jive/pattern/all.hpp"

#include "y/pointer/auto.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"
#include "y/jive/pattern/leading.hpp"

using namespace Yttrium;


namespace  {

    static inline
    void testPattern(const Jive::Pattern &p)
    {
        std::cerr << "-- " << p.name << std::endl;

        { AutoPtr<Jive::Pattern> q = p.clone(); }

        const String fileName = String("ser-") +p.name + ".bin";
        {
            OutputFile fp(fileName);
            p.serialize(fp);
        }

        {
            InputFile fp(fileName);
            AutoPtr<Jive::Pattern> loaded = Jive::Pattern::Load(fp);
            Y_ASSERT(p == *loaded);
        }

        {
            Jive::Leading fc;
            p.glean(fc);
            std::cerr << "fc=" << fc << std::endl;
        }


        
    }


}

Y_UTEST(jive_pattern)
{
    Y_SIZEOF(Jive::Pattern);
    Y_SIZEOF(Jive::Any1);

    { Jive::Any1      p;          testPattern(p); }
    { Jive::Single    p('A');     testPattern(p); }
    { Jive::Range     p('Z','A'); testPattern(p); }
    { Jive::Excluded  p('X');     testPattern(p); }

    {
        Jive::And       p;
        p << 'a' << 'b' << Jive::Within('0','9');
        testPattern(p);
    }

}
Y_UDONE()


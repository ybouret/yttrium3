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

        {
            const String dotName = String("gv-") + p.name + ".dot";
            Vizible::Render(dotName,p);
        }

    }


}

Y_UTEST(jive_pattern)
{
    Y_SIZEOF(Jive::Pattern);
    Y_SIZEOF(Jive::Any1);

    { Jive::Any1      p;          testPattern(p); }
    { Jive::Byte      p('A');     testPattern(p); }
    { Jive::Lump      p('Z','A'); testPattern(p); }
    { Jive::Excluded  p('X');     testPattern(p); }

    {
        Jive::And       p;
        p << 'a' << 'b' << Jive::Within('0','9');
        testPattern(p);
    }

    {
        Jive::Or       p;
        p << Jive::Within('a','z') << Jive::Within('A','Z');
        testPattern(p);
    }

    {
        Jive::None       p;
        p << Jive::Within('0','9') << Jive::Within('A','Z');
        testPattern(p);
    }

    {
        const Jive::Motif m = new Jive::Lump('0','9');
        Jive::Optional    p(m);
        testPattern(p);
    }

    {
        const Jive::Motif m = new Jive::Lump('A','Z');
        Jive::Repeating  p(m,1);
        testPattern(p);
    }

    {
        const Jive::Motif m = new Jive::Lump('a','z');
        Jive::Counting  p(m,1,3);
        testPattern(p);
    }


    {
        AutoPtr<Jive::Pattern> p = new Jive::Lump('A','A');
    }


}
Y_UDONE()


#include "y/jive/pattern/basic/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"

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

}
Y_UDONE()


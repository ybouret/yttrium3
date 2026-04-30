#include "y/jive/pattern/basic/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"

using namespace Yttrium;


namespace  {

    static inline
    void testPattern(const Jive::Pattern &p)
    {
        std::cerr << "-- " << p.name << std::endl;

        { AutoPtr<Jive::Pattern> q = p.clone(); }

        const String fileName = p.name + String(".bin");
        {
            OutputFile fp(fileName);
            p.serialize(fp);
        }

    }


}

Y_UTEST(jive_pattern)
{
    Y_SIZEOF(Jive::Pattern);
    Y_SIZEOF(Jive::Any1);

    { Jive::Any1   p;          testPattern(p); }
    { Jive::Single p('A');     testPattern(p); }
    { Jive::Range  p('Z','A'); testPattern(p); }

}
Y_UDONE()


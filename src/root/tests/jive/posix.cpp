#include "y/jive/pattern/posix.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

namespace
{
    static void testPosix(const char * const name, Pattern * const p )
    {
        assert(name);
        std::cerr << "-- " << name << std::endl;
        const Motif  m(p);
        const String baseName = String("posix-") + name;

        {
            const String dotFile = baseName + ".dot";
            Vizible::Render(dotFile,*p);
        }
    }
}

#define Y_TEST_POSIX(NAME) testPosix(#NAME, posix::NAME() )

Y_UTEST(jive_posix)
{
    Y_TEST_POSIX(lower);
    Y_TEST_POSIX(upper);
    Y_TEST_POSIX(alpha);
    Y_TEST_POSIX(digit);
    Y_TEST_POSIX(alnum);
    Y_TEST_POSIX(xdigit);
    Y_TEST_POSIX(blank);
    Y_TEST_POSIX(space);
    Y_TEST_POSIX(punct);
    Y_TEST_POSIX(core);
    Y_TEST_POSIX(vowel);
    Y_TEST_POSIX(consonant);

}
Y_UDONE()



#include "y/coven/vector.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(coven_vector)
{
    Core::Rand    ran;

    for(size_t dims=1; dims <= 5; ++dims)
    {
        Coven::Metrics metrics(dims);
        Coven::Vector  v(metrics);
        do
        {
            for(size_t i=dims;i>0;--i)
            {
                if( ran() > 0.2f )
                    v[i] = ran.in<int>(-4,4);
            }
        } while( !v.univocal() );
        std::cerr << "v=" << v << std::endl;

        Coven::Vector u(metrics);

        CxxArray<int> a(dims);
        {
            for(size_t i=dims;i>0;--i)
            {
                a[i] = ran.in<int>(-4,4);
            }
            std::cerr << "a=" << a << std::endl;
            const bool ok = v.keepOrtho(u,a);
            std::cerr << "u=" << u << std::endl;
            if(ok)
            {
                std::cerr << "|_ortho" << std::endl;
                Y_ASSERT(u.dot(v) == 0);
            }
            else
                std::cerr << "|_parallel" << std::endl;
        }
    }

    Y_SIZEOF(Coven::Vector);
    
}
Y_UDONE()


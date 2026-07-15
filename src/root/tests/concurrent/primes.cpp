#include "y/calculus/prime/test.hpp"
#include "y/concurrent/api/engine.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/splitting/tile1d.hpp"

using namespace Yttrium;

namespace
{
    class PrimeDetector
    {
    public:
        typedef Concurrent::Splitting::Tile1D<uint32_t> Tile;
        
        inline explicit PrimeDetector(const uint32_t n) :
        nmax(n)
        {

        }

        inline virtual ~PrimeDetector() noexcept {}

        inline void run(const Concurrent::Context &ctx)
        {
            const Tile tile(ctx.size,ctx.rank,3,nmax-2);
            String     fileName = "p";
            fileName += ctx.c_str();
            fileName += ".dat";

            uint32_t u=tile.offset;
            while(!Prime::Test(u)) ++u;
            {
                Y_Giant_Lock();
                std::cerr << tile.c_str() << " : " << tile << " -> " << u << " @" << fileName << std::endl;
            }

            // first prime from the interval
            assert(u>=3);

            // loop
            while(true)
            {
                u += 2;
                if( Prime::Test(u) )
                {

                }

                if(u>=tile.utmost)
                {
                    Y_Giant_Lock();
                    std::cerr << tile.c_str() << " break@" << u << std::endl;
                    break;
                }
            }
        }

        const uint32_t nmax;

    private:
        Y_Disable_Copy_And_Assign(PrimeDetector);
    };
}

#include "y/ascii/convert.hpp"

Y_UTEST(concurrent_primes)
{

    const uint32_t     nmax = argc>1 ? ASCII::Convert::To<uint32_t>(argv[1],"nmax",0) : 1000;
    PrimeDetector      detect(nmax);
    Concurrent::Engine engine( Concurrent::SIMD::InParallel(0) );

    (*engine)(detect, & PrimeDetector::run );




}
Y_UDONE()


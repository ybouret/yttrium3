#include "y/calculus/prime/test.hpp"
#include "y/concurrent/api/engine.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/splitting/tile1d.hpp"
#include "y/stream/libc/output.hpp"
#include "y/format/decimal.hpp"

using namespace Yttrium;

namespace
{

    static inline
    String MakeFileName(const Concurrent::Member &ctx )
    {
        String     fileName = "p";
        fileName += ctx.c_str();
        fileName += ".dat";
        return fileName;
    }

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
            const Tile   tile(ctx.size,ctx.rank,3,nmax-2);
            const String fileName = MakeFileName(ctx);

            uint32_t u=tile.offset;
            while(!Prime::Test(u)) ++u;
            {
                Y_Giant_Lock();
                std::cerr << tile.c_str() << " : " << tile << " -> " << u << " @" << fileName << std::endl;
            }

            // first prime from the interval
            assert(u>=3);
            OutputFile fp(fileName);
            fp << Decimal(u).c_str() << '\n';

            // loop
            while(true)
            {
                u += 2;

                if(u>=tile.utmost)
                {
                    Y_Giant_Lock();
                    std::cerr << tile.c_str() << " break@" << u << std::endl;
                    break;
                }

                if( Prime::Test(u) )
                {
                    fp << Decimal(u).c_str() << '\n';
                }
            }
        }

        const uint32_t nmax;

    private:
        Y_Disable_Copy_And_Assign(PrimeDetector);
    };
}

#include "y/ascii/convert.hpp"
#include "y/vfs/local/fs.hpp"
#include "y/libc/file/copy.hpp"

Y_UTEST(concurrent_primes)
{
    LocalFS &          fs   = LocalFS::Instance();
    const uint32_t     nmax = argc>1 ? ASCII::Convert::To<uint32_t>(argv[1],"nmax",0) : 1000;
    PrimeDetector      detect(nmax);
    Concurrent::Engine engine( Concurrent::SIMD::InParallel(0) );
    (std::cerr << "Computing..." << std::endl).flush();

    (*engine)(detect, & PrimeDetector::run );

    const String fileName = "p.dat";
    {
        const Concurrent::Member primary(engine->size(),0);
        const String             oldPath = MakeFileName(primary);
        fs.moveFile(oldPath,fileName);
    }

    (std::cerr << "Merging..." << std::endl).flush();
    Libc::OutputFile target(fileName,true);
    for(size_t rank=1;rank<engine->size();++rank)
    {
        const Concurrent::Member replica(engine->size(),rank);
        const String             srcName = MakeFileName(replica);
        {
            Libc::InputFile          source(srcName);
            Libc::FileCopy::To(target,source);
        }
        (void) fs.tryRemoveFile(srcName);
    }





}
Y_UDONE()


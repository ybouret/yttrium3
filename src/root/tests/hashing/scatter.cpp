
#include "y/hashing/to.hpp"
#include "y/hashing/md5.hpp"
#include "y/hashing/sha1.hpp"
#include "y/hashing/fnv.hpp"
#include "y/hashing/sha256.hpp"
#include "y/hashing/sha512.hpp"
#include "y/hashing/rmd128.hpp"
#include "y/hashing/rmd160.hpp"
#include "y/hashing/md2.hpp"
#include "y/hashing/md4.hpp"
#include "y/hashing/pjw.hpp"
#include "y/hashing/elf.hpp"
#include "y/hashing/crc32.hpp"
#include "y/hashing/adler32.hpp"

#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/core/hsort.hpp"

#include "y/cameo/addition.hpp"
#include "y/stream/libc/output.hpp"

#include <cmath>

using namespace Yttrium;

namespace
{
    static bool verbose = false;

    template <typename T> static inline
    bool collide(const T &       word,
                 const T * const table,
                 const size_t    n)
    {

        for(size_t i=0;i<n;++i)
            if( word == table[i]) return true;

        return false;
    }

    template <typename T> static inline
    bool collided(const T &       word,
                  T * const       table,
                  const size_t    n)
    {
        if(verbose) std::cerr << " " << Hexadecimal(word);
        table[n]  = word;
        if(collide(word,table,n))
        {
            if(verbose)  std::cerr << "(*)";
            return true;
        }
        else
        {
            if(verbose) std::cerr << "   ";
            return false;
        }
    }

    static inline
    void scatter(Hashing::Function &H)
    {
        uint8_t  table8[256];
        uint16_t table16[256];
        uint32_t table32[256];

        size_t n8 = 0, n16=0, n32=0;
        for(unsigned i=0;i<256;++i)
        {
            const uint8_t  u = (uint8_t)i;
            const uint8_t  b  = Hashing::To<uint8_t>(H,&u,1);
            const uint16_t w  = Hashing::To<uint16_t>(H,&u,1);
            const uint32_t dw = Hashing::To<uint32_t>(H,&u,1);
            if( collided(b,table8,i)  ) ++n8;
            if( collided(w,table16,i) ) ++n16;
            if( collided(dw,table32,i) ) ++n16;
            if(verbose) std::cerr << std::endl;
        }
        std::cerr << "(*) "
        << std::setw(10) << H.callSign() << " collisions :"
        << std::setw(4) << n8  << " | "
        << std::setw(4) << n16 << " | "
        << std::setw(4) << n32 << std::endl;
        if(!n8)
        {
            {
                String     fn = H.callSign(); fn += ".dat";
                OutputFile fp(fn);
                for(unsigned i=0;i<255;++i)
                {
                    fp("%u\n", table8[i]);
                }
            }
            Cameo::Addition<double> xadd(256);
            for(unsigned i=0;i<255;++i)
            {
                const double a = table8[i];
                const double b = table8[i+1];
                xadd << fabs(b-a);
            }
            const double ave = xadd() / 255.0;
            for(unsigned i=0;i<255;++i)
            {
                const double a = table8[i];
                const double b = table8[i+1];
                const double c = fabs(b-a);
                const double d = c - ave;
                xadd << d*d;
            }
            const double sig = sqrt( xadd() / 255.0 );
            std::cerr << "\t\tave = " << ave << std::endl;
            std::cerr << "\t\tsig = " << sig << std::endl;


            Core::HSort::Increasing(table8,256);
            for(unsigned i=0;i<256;++i)
            {
                Y_ASSERT(i==table8[i]);
            }
            std::cerr << "    " << std::setw(10) << H.callSign() << " is a 8-bits permutation" << std::endl;
        }
    }
}

#include "y/ascii/convert.hpp"
#include "y/stream/libc/output.hpp"
#include "y/format/decimal.hpp"
#include "y/string/env.hpp"

Y_UTEST(hashing_scatter)
{
    verbose = Environment::Flag("VERBOSE");
    Hashing::MD2    md2;
    Hashing::MD4    md4;
    Hashing::MD5    md5;
    Hashing::SHA1   sha1;
    Hashing::FNV    fnv;
    Hashing::PJW    pjw;
    Hashing::ELF    elf;
    Hashing::SHA224 sha224;
    Hashing::SHA256 sha256;
    Hashing::SHA384 sha384;
    Hashing::SHA512 sha512;
    Hashing::RMD128 rmd128;
    Hashing::RMD160 rmd160;
    Hashing::CRC32  crc32;
    Hashing::Adler32 adler32;

    scatter(md2);
    scatter(md4);
    scatter(md5);
    scatter(sha1);
    scatter(sha224);
    scatter(sha256);
    scatter(sha384);
    scatter(sha512);
    scatter(rmd128);
    scatter(rmd160);

    scatter(fnv);
    scatter(pjw);
    scatter(elf);
    scatter(crc32);
    scatter(adler32);



}
Y_UDONE()

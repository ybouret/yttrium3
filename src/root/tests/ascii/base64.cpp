#include "y/ascii/base64.hpp"
#include "y/libc/block/zero.h"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
	static inline void printRange(const char ini, const unsigned n)
	{
		for (unsigned i = 0; i < n; ++i)
		{
			std::cerr << '\'' << (char)(ini + i) << '\'' << ',';
		}
		std::cerr << std::endl;
	}

	static inline void print62()
	{
		printRange('A', 26);
		printRange('a', 26);
		printRange('0', 10);
	}
}

Y_UTEST(ascii_base64)
{
    if(false)
    {
        print62();
        std::cerr << "'+','/'" << std::endl;

        std::cerr << std::endl;

        print62();
        std::cerr << "'-','_'" << std::endl;

        std::cerr << std::endl;
    }

    if(true)
    {
        unsigned i = 0;
        for(unsigned j=0;j<16;++j)
        {
            for(unsigned k=0;k<16;++k,++i)
            {
                const char c = (char)i;
                std::cerr << std::setw(3) << (unsigned) ASCII::Base64::Encoding(c);
                if(i<255) std::cerr << ',';
            }
            std::cerr << std::endl;
        }
    }

    char out[8];
    Y_BZero(out);
    ASCII::Base64::Encode1(out,'A');
    std::cerr << out << std::endl;

    Y_BZero(out);
    ASCII::Base64::Encode2(out,'A','K');
    std::cerr << out << std::endl;

    Y_BZero(out);
    ASCII::Base64::Encode3(out,'A','K','Z');
    std::cerr << out << std::endl;
}
Y_UDONE()

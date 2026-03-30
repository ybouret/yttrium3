#include "y/ascii/base64.hpp"
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
	print62();
	std::cerr << "'+','/'" << std::endl;
	
	std::cerr << std::endl;

	print62();
	std::cerr << "'-','_'" << std::endl;

	std::cerr << std::endl;

}
Y_UDONE()

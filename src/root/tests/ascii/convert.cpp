


#include "y/ascii/convert.hpp"
#include "y/libc/str/len.h"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(ascii_convert)
{
	for (int i = 1; i < argc; ++i)
	{
		const char* const text = argv[i];
		const size_t      size = Yttrium_Strlen(text);
		const int         I = ASCII::Convert::To<int>(text, size, "int", 0);
		const uint16_t    U = ASCII::Convert::To<uint16_t>(text, size, "uint16_t", 0);
		const apn         N = ASCII::Convert::To<apn>(text, size, "apn", 0);
		const apz         Z = ASCII::Convert::To<apz>(text, size, "apz", 0);
		const float       f = ASCII::Convert::To<float>(text, size, "float", 0);
		const double      d = ASCII::Convert::To<double>(text, size, "double", 0);
		const long double l = ASCII::Convert::To<long double>(text, size, "long double", 0);

		std::cerr << "I = " << I << std::endl;
		std::cerr << "U = " << U << std::endl;
		std::cerr << "N = " << N << std::endl;
		std::cerr << "Z = " << Z << std::endl;
		std::cerr << "f = " << f << std::endl;
		std::cerr << "d = " << d << std::endl;
		std::cerr << "l = " << l << std::endl;

	}
}
Y_UDONE()

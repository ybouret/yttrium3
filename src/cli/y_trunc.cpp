
#include "y/stream/libc/input.hpp"
#include "y/system/program.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

Y_PROGRAM()
{
	size_t nmin = 0;
	size_t nmax = nmin;

	switch (argc - 1)
	{
	case 1: nmin = nmax = ASCII::Convert::To<size_t>(argv[1],"nmin",0); break;
	case 2:
		nmin = ASCII::Convert::To<size_t>(argv[1],"nmin",0);
		nmax = ASCII::Convert::To<size_t>(argv[2],"nmax",0); break;
	default:
		std::cerr << "usage: " << program << " nmax | nmin nmax" << std::endl;
		return 1;
	}

	InputFile fp(StdIn);
	String    line;
	while (fp.gets(line))
	{
		const size_t n = line.size();
		if (n >= nmin && n <= nmax) std::cout << line << std::endl;
	}

}
Y_EXECUTE()

#include "y/container/associative/book.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

#include "y/object.hpp"
#include "y/pointer/auto.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/container/associative/hash/default-set.hpp"
#include "y/core/display.hpp"

Y_UTEST(container_book)
{
	{
		int a = 7;
		AddrKey k(a);
		std::cerr << (void*)&a << " => " << k << std::endl;
	}

	{
		AutoPtr<Object> p = new Object();
		Object& r = *p;
		AddrKey k(r);
		std::cerr << (void*)&r << " => " << k << std::endl;
	}

	int arr[8] = { 1,2,3,4,5,6,7,8 };

	BookOf<int, SuffixSet>            sbook;
	BookOf<const int, DefaultHashSet> hbook;

	for (size_t i = 0; i < 8; ++i)
	{
		Y_ASSERT(sbook.write(arr[i]));
		Y_ASSERT(hbook.write(arr[i]));
		Y_ASSERT(!sbook.write(arr[i]));
		Y_ASSERT(!hbook.write(arr[i]));
		Y_ASSERT(sbook.query(arr[i]));
		Y_ASSERT(hbook.query(arr[i]));
	}
	
	Core::Display(std::cerr, sbook.begin(), sbook.size()) << std::endl;
	Core::Display(std::cerr, hbook.begin(), hbook.size()) << std::endl;

}
Y_UDONE()


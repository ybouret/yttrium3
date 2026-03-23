#include "y/libc/sort.h"
#include "y/random/shuffle.hpp"
#include "y/core/rand.hpp"
#include "y/core/display.hpp"
#include "y/core/find.hpp"
#include "y/utest/run.hpp"
#include <ctime>

using namespace Yttrium;

namespace
{
	template <typename T> static inline
		int Comparing(const void* const lhs, const void* const rhs, void*)
	{
		const T& L = *static_cast<const T*>(lhs);
		const T& R = *static_cast<const T*>(rhs);
		return L < R ? -1 : (R < L ? 1 : 0);
	}
}

Y_UTEST(libc_sort)
{
	Core::Rand   ran((long)time(NULL));
	size_t       arr[9] = { 0 };
    const size_t num = Y_Static_Size(arr);

    std::cerr << "Sorting" << std::endl;
	for (size_t i = 0; i < num; ++i) arr[i] = i;
	Core::Display(std::cerr, arr, num) << std::endl;

	for (size_t iter = 0; iter < 20; ++iter)
	{
		Random::Shuffle(ran, arr, num);
		Core::Display(std::cerr, arr, num) << " -> ";
		for (size_t i = 0; i < num; ++i)
		{
			if (!Core::Find(i, arr, num))
			{
				std::cerr << "missing " << i << std::endl;
				return 1;
			}
		}
		size_t tmp = 0;
		Yttrium_Sort(arr, num, sizeof(arr[0]), Comparing<size_t>, NULL, &tmp);
		Core::Display(std::cerr, arr, num);

		for (size_t i = 0; i < num; ++i)
		{
			if (i != arr[i])
			{
				std::cerr << " invalid " << i << std::endl;
				return 1;
			}
		}

		std::cerr << std::endl;
	}

    std::cerr << std::endl;
    std::cerr << "Co-Sorting" << std::endl;
    char chr[num];


    for(size_t iter=0;iter<10;++iter)
    {
        Random::Shuffle(ran, arr, num);
        for(size_t i=0;i<num;++i) chr[i] = 'a' + (char)i ;
        Core::Display(std::cerr, arr, num) << " <== ";
        Core::Display(std::cerr, chr, num) << std::endl;

        {
            size_t s = 0;
            char   c = 0;
            Yttrium_CoSort(arr, num, sizeof(arr[0]), Comparing<size_t>, NULL, &s,
                           chr, sizeof(chr[0]), &c);
        }
        Core::Display(std::cerr, arr, num) << " ==> ";
        Core::Display(std::cerr, chr, num) << std::endl;

        for (size_t i = 0; i < num; ++i)
        {
            const char lhs = (char)i + 'a';
            if (!Core::Find(lhs, chr, num))
            {
                std::cerr << "missing " << lhs << std::endl;
                return 1;
            }
        }

        for (size_t i = 0; i < num; ++i)
        {
            if (i != arr[i])
            {
                std::cerr << " invalid " << i << std::endl;
                return 1;
            }
        }


    }




}
Y_UDONE()


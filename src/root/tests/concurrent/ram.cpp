#include "y/concurrent/nucleus.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/libc/block/zero.h"

using namespace Yttrium;

namespace
{
	struct Block
	{
		void* addr;
		size_t size;
	};
}
Y_UTEST(concurrent_ram)
{
	Concurrent::Nucleus& nucleus = Concurrent::Nucleus::Instance();
	Core::Rand  ran;

	Block        block[1000];
	const size_t nmax = Y_Static_Size(block);

	Y_BZero(block);

	for (size_t i = 0; i < nmax; ++i)
	{
		block[i].addr = nucleus.acquire(block[i].size = ran.leq<size_t>(1000));
	}


	Random::Shuffle(ran, block, nmax);
	for (size_t i = 0; i < nmax; ++i)
	{
		nucleus.release(block[i].addr, block[i].size);
	}

	Y_PRINTV(Concurrent::Nucleus::RAM);
	//Y_CHECK(0 == Concurrent::Nucleus::RAM);


}
Y_UDONE()


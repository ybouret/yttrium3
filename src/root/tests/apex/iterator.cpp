#include "y/apex/api/iterator.hpp"
#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"



using namespace Yttrium;

namespace
{
	template <typename T> static inline
		void testIter(const T* const data, const size_t bytes)
	{
		Apex::ByteIterator<T> iter(data);
		for (size_t i = 1; i <= bytes; ++i)
		{
			const uint8_t byte = iter();
			Y_PRINTV(Hexadecimal(byte));
		}
		std::cerr << std::endl;
	}
}
Y_UTEST(apex_iterator)
{
	{
		const uint8_t               data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		Apex::ByteIterator<uint8_t> iter(data);
		for (size_t i = 1; i <= 8; ++i)
		{
			const uint8_t byte = iter();
			Y_ASSERT(iter.within(data, sizeof(data) / sizeof(data[0]) + 1));
			Y_PRINTV(Hexadecimal(byte));
		}

		std::cerr << std::endl;
	}

	{
		const uint16_t               data[4] = { 0x0201, 0x0403, 0x0605, 0x0807 };
		Apex::ByteIterator<uint16_t> iter(data);
		for (size_t i = 1; i <= 8; ++i)
		{
			const uint8_t byte = iter();
			Y_ASSERT(iter.within(data, sizeof(data) / sizeof(data[0]) + 1));
			Y_PRINTV(Hexadecimal(byte));
		}
		std::cerr << std::endl;
	}

	{
		const uint32_t               data[2] = { 0x04030201, 0x08070605 };
		Apex::ByteIterator<uint32_t> iter(data);
		for (size_t i = 1; i <= 8; ++i)
		{
			const uint8_t byte = iter();
			Y_ASSERT(iter.within(data, sizeof(data) / sizeof(data[0]) + 1));
			Y_PRINTV(Hexadecimal(byte));
		}
		std::cerr << std::endl;
	}

	const size_t size = 8;
	void* const  addr = calloc(1, size);
	if (addr)
	{
		{
			uint8_t* const data = static_cast<uint8_t*>(addr);
			data[0] = 1;
			data[1] = 2;
			data[2] = 3;
			data[3] = 4;
			data[4] = 5;
			data[5] = 6;
			data[6] = 7;
			data[7] = 8;
			testIter<uint8_t>(data,size);
		}

		{
			uint16_t* const data = static_cast<uint16_t*>(addr);
			data[0] = 0x0201;
			data[1] = 0x0403;
			data[2] = 0x0605;
			data[3] = 0x0807;
			testIter<uint16_t>(data, size);
		}

		{
			uint32_t* const data = static_cast<uint32_t*>(addr);
			data[0] = 0x04030201;
			data[1] = 0x08070605;
			testIter<uint32_t>(data, size);
		}

		free(addr);
	}


}
Y_UDONE()


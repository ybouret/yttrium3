#include "y/ascii/base64.hpp"
#include <cassert>

namespace Yttrium
{
	namespace ASCII
	{
		const char Base64::STD[64] =
		{
			'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
			'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
			'0','1','2','3','4','5','6','7','8','9',
			'+','/'
		};

		const char Base64::URL[64] =
		{
			'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
			'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
			'0','1','2','3','4','5','6','7','8','9',
			'-','_'
		};

		static const uint8_t hi6 = 128 + 64 + 32 + 16 + 8 + 4;
		static const uint8_t lo2 = 2 + 1;

		void Base64::Encode1(char* const out, const uint8_t b0, const bool pad, const char* const table) noexcept
		{
			assert(table);
			assert(out);

			const uint8_t u0 = (uint8_t)((b0 & hi6) >> 2); assert(u0 < 64);
			const uint8_t u1 = (uint8_t)((b0 & lo2) << 4); assert(u1 < 64);
			out[0] = table[u0];
			out[1] = table[u1];
			if (pad) out[2] = out[3] = Pad;

		};
	}


}

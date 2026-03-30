#include "y/ascii/base64.hpp"
#include "y/core/min.hpp"
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

        static inline uint8_t GetEncoding(const char * const table, const char C) noexcept
        {
            assert(table);
            for(size_t i=0;i<64;++i)
                if( C == table[i]) return i;
            return 0xff;
        }

        uint8_t Base64::Encoding(const char C) noexcept
        {
            return Min( GetEncoding(STD,C), GetEncoding(URL,C) );
        }

		static const uint8_t hi6 = 128 + 64 + 32 + 16 + 8 + 4;
		static const uint8_t lo2 = 2 + 1;


		void Base64::Encode1(char* const out, const uint8_t b0, const bool pad, const char* const table) noexcept
		{
			assert(table);
			assert(out);

			const uint8_t u0 = (uint8_t)( (b0 & hi6) >> 2 );
			const uint8_t u1 = (uint8_t)( (b0 & lo2) << 4 );
            assert(u0 < 64);
            assert(u1 < 64);
			out[0] = table[u0];
			out[1] = table[u1];
			if (pad) out[2] = out[3] = Pad;
        };

        static const uint8_t hi4 = 128 + 64 + 32 + 16;
        static const uint8_t lo4 = 1+2+4+8;

        void Base64::Encode2(char* const out, const uint8_t b0, const uint8_t b1, const bool pad, const char* const table) noexcept
        {
            assert(table);
            assert(out);

            const uint8_t u0 = (uint8_t)(   (b0 & hi6) >> 2);
            const uint8_t u1 = (uint8_t)( ( (b0 & lo2) << 4) | ( (b1 & hi4) >> 4) );
            const uint8_t u2 = (uint8_t)(   (b1 & lo4) << 2);
            assert(u0 < 64);
            assert(u1 < 64);
            assert(u2 < 64);
            out[0] = table[u0];
            out[1] = table[u1];
            out[2] = table[u2];
            if(pad) out[3] = Pad;
        };

        static const uint8_t hi2 = 128+64;
        static const uint8_t lo6 = 1+2+4+8+16+32;

        void Base64::Encode3(char* const out, const uint8_t b0, const uint8_t b1, const uint8_t b2, const char* const table) noexcept
        {
            assert(table);
            assert(out);

            const uint8_t u0 = (uint8_t)(  (b0 & hi6) >> 2);
            const uint8_t u1 = (uint8_t)( ((b0 & lo2) << 4) | ( (b1 & hi4) >> 4) );
            const uint8_t u2 = (uint8_t)( ((b1 & lo4) << 2) | ( (b2 & hi2) >> 6) );
            const uint8_t u3 = (uint8_t)(   b2 & lo6 );

            assert(u0 < 64);
            assert(u1 < 64);
            assert(u2 < 64);
            assert(u3 < 64);

            out[0] = table[u0];
            out[1] = table[u1];
            out[2] = table[u2];
            out[3] = table[u3];
        };

        const uint8_t Base64:: LUT[256] =
        {
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255, 62,255, 62,255, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61,255,255,255,255,255,255,
            255,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,255,255,255,255, 63,
            255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
            255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
        };
	}


}

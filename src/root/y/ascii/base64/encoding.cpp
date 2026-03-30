
#include "y/ascii/base64/encoding.hpp"
#include "y/core/min.hpp"
#include <cassert>

namespace Yttrium
{
    namespace ASCII
    {
        namespace Base64
        {
            const char Encoding::STD[64] =
            {
                'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                '0','1','2','3','4','5','6','7','8','9',
                '+','/'
            };

            const char Encoding::URL[64] =
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

            uint8_t Encoding::GetByte(const char C) noexcept
            {
                return Min( GetEncoding(STD,C), GetEncoding(URL,C) );
            }

            static const uint8_t hi6 = 128 + 64 + 32 + 16 + 8 + 4;
            static const uint8_t lo2 = 2 + 1;


            void Encoding::Encode1(char* const out, const uint8_t b0, const bool pad, const char* const table) noexcept
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

            void Encoding::Encode2(char* const out, const uint8_t b0, const uint8_t b1, const bool pad, const char* const table) noexcept
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

            void Encoding::Encode3(char* const out, const uint8_t b0, const uint8_t b1, const uint8_t b2, const char* const table) noexcept
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

            size_t Encoding:: Encode(char *             output,
                                     const uint8_t *    input,
                                     const size_t       length,
                                     const bool         pad,
                                     const char * const table) noexcept
            {
                static const size_t three = 3;
                assert(!(0==output&&length>0));
                assert(!(0==input&&length>0));

                const size_t num3To4 = length / three;
                size_t       result  = num3To4 * 4;
                for(size_t i=num3To4;i>0;--i)
                {
                    Encode3(output,input[0],input[1],input[2],table);
                    output += 4;
                    input  += 3;
                }

                switch(length%three)
                {
                    case 1:
                        Encode1(output,input[0],pad,table);
                        result += pad ? 4 : 2;
                        break;

                    case 2:
                        Encode2(output,input[0],input[1],pad,table);
                        result += pad ? 4 : 3;
                        break;
                        
                    default:
                        assert(0==(length%three));
                        break;

                }

                return result;

            }
        }

    }
}

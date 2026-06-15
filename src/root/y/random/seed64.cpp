
#include "y/random/seed64.hpp"
#include "y/check/crc32.hpp"
#include "y/system/pid.hpp"
#include "y/hashing/des64.hpp"

#include "y/format/hexadecimal.hpp"
#include <ctime>
#include <iostream>

namespace Yttrium
{
    namespace Random
    {
        static inline
        uint32_t _seed64_lo() noexcept
        {
            const time_t t = time(NULL);
            return CRC32::Run(t,0);
        }

        static inline
        uint32_t _seed64_up() noexcept
        {
            const uint64_t pid = System::ProcessID::Get();
            return CRC32::Run(pid,0);
        }

        uint64_t Seed64:: Get64() noexcept
        {
            Hashing::DES64 m64;
            union
            {
                uint64_t qw;
                uint32_t dw[2];
            } alias = { 0 };

            alias.dw[0] = _seed64_lo();
            alias.dw[1] = _seed64_up();
            //std::cerr << Hexadecimal(alias.dw[0]) << "|" << Hexadecimal(alias.dw[1]) << " => " << Hexadecimal(alias.qw) << std::endl;
            m64(alias.dw[0],alias.dw[1]);
            //std::cerr << Hexadecimal(alias.dw[0]) << "|" << Hexadecimal(alias.dw[1]) << " => " << Hexadecimal(alias.qw) << std::endl;
            return alias.qw;
        }

        
        uint32_t Seed64:: Get32() noexcept
        {
            const uint64_t qw = Get64();
            return CRC32::Run(qw,0);
        }

        uint16_t Seed64:: Get16() noexcept
        {
            const uint64_t qw = Get64();
            return (uint16_t)CRC32::Run(qw,0);
        }

        uint8_t Seed64:: Get8() noexcept
        {
            const uint64_t qw = Get64();
            return (uint8_t)CRC32::Run(qw,0);
        }




    }

}



#include "y/container/associative/addr-key.hpp"
#include "y/format/hexadecimal.hpp"
#include <cstring>


namespace Yttrium
{

    AddrKey:: AddrKey(const AddrKey &k) noexcept :
    Memory::ReadOnlyBuffer(),
    data()
    {
        memcpy(data,k.data,sizeof(data));
    }

    std::ostream & operator<<(std::ostream &os, const AddrKey &key)
    {
        char s[ 2*AddrKey::Length + 2];
        memset(s,0,sizeof(s));
        for(size_t i=0;i<AddrKey::Length;++i)
        {
            const char * const h = Hexadecimal::LowerByte[key.data[i]];
            strcat(s,h);
        }
        return os << s;
    }


    const void * AddrKey:: ro() const noexcept
    {
        return data;
    }

    size_t AddrKey:: length() const noexcept
    {
        return sizeof(void*);
    }

    void AddrKey:: fillWith(const void * const addr) noexcept
    {
        UType    word = (UType)addr;
        for(size_t i=Length;i>0;)
        {
            data[--i] = (uint8_t) word;
            word  >>= 8;
        }
    }


    AddrKey:: ~AddrKey() noexcept
    {
        memset(data,0,sizeof(data));
    }

}

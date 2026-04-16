
#include "y/stream/input.hpp"
#include "y/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{

    InputStream::  InputStream() : Stream() {}
    InputStream:: ~InputStream() noexcept {}

    bool InputStream:: peek(char &C)
    {
        if( query(C) )
        {
            store(C);
            return true;
        }
        else
            return false;
    }

    bool InputStream:: gets(String &s)
    {
        s.free();

    GETCHAR:
        {
            char c = 0;
            if(!query(c))
                return s.size()>0;

            switch(c)
            {

                case CR:
                    if(query(c)) {
                        if(LF!=c)
                            store(c);
                    }
                    return true;

                case LF: return true;
                default: break;

            }
            s += c;
            goto GETCHAR;
        }



        return false;
    }

    void InputStream:: load(void * const       blockAddr,
                            const size_t       blockSize,
                            const char * const varName,
                            const char * const varPart)
    {
        assert(blockAddr);
        assert(blockSize);
        const size_t numRead = query(blockAddr,blockSize);
        if(numRead<blockSize)
        {
            const size_t missing = blockSize - numRead;
            Specific::Exception excp(title.c_str(),"#missing=%s", Decimal(missing).c_str());
            throw excp.signedFor(varName,varPart);
        }
    }

    template <>
    uint8_t InputStream:: load<uint8_t>(const char * const varName,
                                        const char * const varPart)
    {
        uint8_t res = 0;
        load(&res,1,varName,varPart);
        return res;
    }

    template <>
    uint16_t InputStream:: load<uint16_t>(const char * const varName,
                                          const char * const varPart)
    {
        uint8_t u[2] = {0,0};
        load(u,2,varName,varPart);
        const uint16_t u0 = u[0];
        const uint16_t u1 = u[1];
        return u0 | (u1<<8);
    }

    template <>
    uint32_t InputStream:: load<uint32_t>(const char * const varName,
                                          const char * const varPart)
    {
        uint8_t u[4] = {0,0,0,0};
        load(u,4,varName,varPart);
        const uint32_t u0 = u[0];
        const uint32_t u1 = u[1];
        const uint32_t u2 = u[2];
        const uint32_t u3 = u[3];
        return u0 | (u1<<8) | (u2<<16) | (u3<<24);
    }

    template <>
    uint64_t InputStream:: load<uint64_t>(const char * const varName,
                                          const char * const varPart)
    {
        uint8_t u[8] = {0,0,0,0,0,0,0,0};
        load(u,8,varName,varPart);
        const uint64_t u0 = u[0];
        const uint64_t u1 = u[1];
        const uint64_t u2 = u[2];
        const uint64_t u3 = u[3];
        const uint64_t u4 = u[4];
        const uint64_t u5 = u[5];
        const uint64_t u6 = u[6];
        const uint64_t u7 = u[7];
        return u0 | (u1<<8) | (u2<<16) | (u3<<24) | (u4<<32) | (u5<<40) | (u6<<48) | (u7<<56);
    }






}


#include "y/stream/io/decode64.hpp"

namespace Yttrium
{
    uint64_t InputStream:: vbr64(const char * const varName,
                                 const char * const varPart)
    {
        // read the first byte
        const uint8_t ini = load<uint8_t>(varName,varPart);
        IO::Decode64  dec(ini,varName,varPart);

        assert(dec.expected<=8);
        const size_t  n    = dec.expected;
        if(n>0)
        {
            // read the expected bytes
            uint8_t       u[8] = {0,0,0,0,0,0,0,0};
            load(u,n,varName,varPart);

            // decode the extra bytes
            for(size_t k=0;k<n;++k) dec(u[k],varName,varPart);
        }

        // return value
        return dec.value;
    }
}

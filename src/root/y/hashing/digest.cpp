#include "y/hashing/digest.hpp"
#include "y/memory/troop/legacy.hpp"

#include "y/format/hexadecimal.hpp"
#include "y/type/destroy.hpp"
#include "y/string/length.hpp"
#include "y/calculus/alignment.hpp"
#include "y/pointer/auto.hpp"
#include "y/ascii/printable.hpp"
#include "y/exception.hpp"

#include <cstring>

namespace Yttrium
{
    namespace Hashing
    {

        typedef Memory::LegacyTroop<uint8_t,Object> DigestMemory;

        class Digest::Code :   public DigestMemory
        {
        public:
            inline explicit Code(const size_t n) :
            DigestMemory(n),
            width(n)
            {
                assert(width>0);
            }

            inline explicit Code(const Code &other) :
            DigestMemory(other.width),
            width(other.width)
            {
                memcpy(addr,other.addr,width);
            }

            inline virtual ~Code() noexcept
            {

            }

            static inline int GetHex(const char c)
            {
                const int res = Hexadecimal::ToDec(c);
                if(res<0) throw Specific::Exception(CallSign,"invalid hexadecimal '%s'", ASCII::Printable::Text(c) );
                return res;
            }

            static inline Code * Hex(const char *hex)
            {
                const size_t  n    = StringLength(hex);
                const size_t  w    = Alignment::On<2>::Ceil(n)/2;
                AutoPtr<Code> code = new Code(w);
                uint8_t *p   = code->addr;
                size_t  rem  = n;
                if(1&rem)
                {
                    const int lo = GetHex( *(hex++) );
                    *(p++) = static_cast<uint8_t>(lo);
                    --rem;
                }
                assert(!(1&rem));

                while(rem>0)
                {
                    const int hi = GetHex( *(hex++) ); --rem;
                    const int lo = GetHex( *(hex++) ); --rem;
                    *(p++) = static_cast<uint8_t>(lo + (hi<<4) );
                }

                
                return code.yield();
            }

            inline String str() const
            {
                const size_t w2 = width<<1;
                String s(WithAtLeast,w2,InitBlankString); assert(w2==s.size());

                char * target = (char *)(s.c_str());
                for(size_t i=0;i<width;++i,target+=2)
                {
                    const char * const hx = Hexadecimal::LowerByte[ uint8_t(addr[i]) ]; assert(hx); assert(2==strlen(hx));
                    memcpy(target,hx,2);
                }

                return s;
            }


            const size_t width;

        private:
            Y_Disable_Assign(Code);
        };


        const char * const Digest::CallSign = "Hashing::Digest";

        Digest:: Digest(const size_t width) :
        code( new Code(width) )
        {
        }

        Digest:: Digest(const Digest &other) :
        Container(),
        ContiguousWritable<uint8_t>(),
        Memory::ReadWriteBuffer(),
        code( new Code( *other.code) )
        {
        }

        Digest:: Digest(const char * const hex) :
        code( Code::Hex(hex) )
        {

        }



        Digest:: ~Digest() noexcept
        {
            if(code) Destroy(code);
        }


        const void * Digest:: ro() const noexcept
        {
            assert(code); return code->addr;
        }

        size_t Digest:: length() const noexcept
        {
            assert(code); return code->width;
        }

        size_t Digest:: size() const noexcept
        {
            assert(code); return code->width;
        }

        size_t Digest:: capacity() const noexcept
        {
            assert(code); return code->width;
        }

        const uint8_t & Digest:: ask(const size_t indx) const  noexcept
        {
            assert(code);
            assert(indx>0);
            assert(indx<=code->width);
            return code->cxx[indx];
        }


        String Digest:: str() const noexcept
        {
            assert(code);
            return code->str();
        }

        std::ostream & operator<<(std::ostream &os, const Digest &d)
        {
            return os << d.str();
        }

        void Digest:: ldz() noexcept
        {
            assert(0!=code);
            memset(code->addr,0,code->width);
        }

    }
}

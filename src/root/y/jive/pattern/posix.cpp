
#include "y/jive/pattern/posix.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"

#include <cstring>

namespace Yttrium
{
    namespace Jive
    {
        Pattern * posix:: lower()
        {
            return new Lump('a','z');
        }

        Pattern * posix:: upper()
        {
            return new Lump('A','Z');
        }

        Pattern * posix:: alpha()
        {
            AutoPtr<Logic> p = new Or();
            *p << upper();
            *p << lower();
            return p.yield();
        }

        Pattern * posix:: digit()
        {
            return new Lump('0','9');
        }

        Pattern * posix:: alnum()
        {
            AutoPtr<Logic> p = new Or();
            *p << digit();
            *p << upper();
            *p << lower();
            return p.yield();
            //return Pattern::Optimize(p.yield());
        }

        Pattern * posix:: word()
        {
            AutoPtr<Logic> p = new Or();
            *p << '_';
            *p << digit();
            *p << upper();
            *p << lower();
            return p.yield();
            //return Pattern::Optimize(p.yield());
        }

        Pattern * posix:: xdigit()
        {
            AutoPtr<Logic> p = new Or();
            *p << digit();
            *p << Within('A','F');
            *p << Within('a','f');
            return p.yield()->optimized();
        }

        Pattern * posix:: blank()
        {
            static const char data[] = " \t";
            return Pattern::Among(data);
        }

        Pattern * posix:: space()
        {
            return Pattern::Among(" \t\n\r\v\f");
        }

        Pattern * posix::punct()
        {
            return Pattern::Among("][!\"#$%&'()*+,./:;<=>?@\\^_`{|}~-");
        }

        Pattern * posix:: core()
        {
            AutoPtr<Logic> p = new Or();
            *p << 0x20;
            *p << 0x21;
            *p << Within(0x23,0x26);
            *p << Within(0x28,0x5B);
            *p << Within(0x5D,0x7F);
            return  p.yield()->optimized();
        }

        static const char __vowels__[] = "aeiouyAEIOUY";

        Pattern * posix:: vowel()
        {
            return Pattern::Among(__vowels__);
        }

        Pattern * posix:: consonant()
        {
            AutoPtr<Logic> p = new Or();
            for(int i='a';i<='z';++i)
            {
                if(strchr(__vowels__,i)) continue;
                *p << uint8_t(i);
            }

            for(int i='A';i<='Z';++i)
            {
                if(strchr(__vowels__,i)) continue;
                *p << uint8_t(i);
            }
            return p.yield()->optimized();
        }

        static inline void __fill_endl( Patterns &ops )
        {
            ops.pushTail( new Byte('\n') );
            ops.pushTail( new Byte('\r') );
            ops.pushTail( Pattern::Exact("\r\n") );
        }

        Pattern * posix:: endl()
        {
            AutoPtr<Logic> p = new Or();
            __fill_endl(*p);
            return  p.yield()->optimized();
        }

        Pattern * posix:: dot()
        {
            AutoPtr<Logic> p = new None();
            __fill_endl(*p);
            return  p.yield()->optimized();
        }

        Pattern * posix::any1()
        {
            return new Any1();
        }


#define Y_Jive_Posix(NAME) if(id == #NAME) return NAME()

        Pattern * posix:: named(const String &id) noexcept
        {
            Y_Jive_Posix(lower);
            Y_Jive_Posix(upper);
            Y_Jive_Posix(alpha);
            Y_Jive_Posix(digit);
            Y_Jive_Posix(alnum);
            Y_Jive_Posix(word);
            Y_Jive_Posix(xdigit);
            Y_Jive_Posix(blank);
            Y_Jive_Posix(space);
            Y_Jive_Posix(punct);
            Y_Jive_Posix(core);
            Y_Jive_Posix(vowel);
            Y_Jive_Posix(consonant);
            Y_Jive_Posix(endl);
            Y_Jive_Posix(dot);
            Y_Jive_Posix(any1);
            return 0;
        }

        Pattern * posix:: named(const char * const id)
        {
            const String _(id);
            return named(_);
        }


    }
}


#include "y/jive/source.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Source:: ~Source() noexcept
        {
            assert(impl);
            Destroy(impl);
        }

        Source:: Source(Module * const m) noexcept :
        InputStream(m->title),
        impl(m),
        buff()
        {
            
        }

        Char * Source:: get()
        {
            return buff.size ? buff.popHead() : impl->get();
        }

        void Source:: unget(Char *const ch) noexcept
        {
            assert(ch);
            buff.pushHead(ch);
        }

        void Source:: unget(Token &token) noexcept
        {
            buff.mergeHead(token);
        }

        void Source:: uncpy(const Token &token)
        {
            Token _(token);
            buff.mergeHead(_);
        }

        void Source:: skip(size_t n) noexcept
        {
            assert(buff.size>=n);
            while(n-- > 0) delete buff.popHead();
        }

        size_t Source:: cached() const noexcept
        {
            return buff.size;
        }


        const Char * Source:: peek()
        {
            if(buff.size)
            {
                return buff.head;
            }
            else
            {
                Char * const ch = impl->get();
                return ch ? buff.pushTail(ch) : 0;
            }
        }

        bool Source:: query(char &c)
        {
            Char * const ch = get();
            if(ch)
            {
                c = **ch;
                delete ch;
                return true;
            }
            else
            {
                return false;
            }
        }

        size_t Source:: query(void * const buffer, const size_t buflen)
        {
            size_t  n  = 0;
            char *  p = (char *)buffer;
            while(n<buflen && buff.size>0)
            {
                *(p++) = **buff.head;
                delete buff.popHead();
                ++n;
            }

            while(n<buflen)
            {
                Char * const ch = impl->get();
                if(!ch) break;
                *(p++) = **ch;
                ++n;
                delete ch;
            }

            return n;
        }

        void Source:: store(const char c)
        {
            buff.pushHead( new Char(*impl,c) );
        }

        void Source:: endl() noexcept
        {
            impl->newLine();
        }

        void Source:: fetch(size_t n)
        {
            while(n-- > 0)
            {
                Char * const ch = impl->get();
                if(!ch) return;
                buff.pushTail(ch);
            }
        }


    }
}


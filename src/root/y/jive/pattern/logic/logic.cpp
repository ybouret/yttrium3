
#include "y/jive/pattern/logic/logic.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Logic:: ~Logic() noexcept
        {
        }


        Logic:: Logic(const uint32_t t) noexcept : Pattern(t), Patterns()
        {
        }

        Logic:: Logic(const Logic &other) : Pattern(other), Patterns(other)
        {
        }

        size_t Logic:: serialize(OutputStream &fp) const
        {
            size_t res = emitUUID(fp);
            res       += fp.vbr(size);
            for(const Pattern *p=head;p;p=p->next)
                res += p->serialize(fp);
            return res;
        }

        void Logic:: load(InputStream &fp)
        {
            const size_t num = fp.vbr<size_t>("Jive::Logic","size");
            for(size_t i=0;i<num;++i)
                pushTail( Load(fp) );
        }

        Logic & Logic:: operator<<(Pattern * const p)
        {
            assert(p);
            pushTail(p);
            return *this;
        }

        bool Logic:: HaveSamePatterns(const Logic &lhs, const Logic &rhs) noexcept
        {
            if(lhs.size!=rhs.size) return false;

            for(const Pattern *l = lhs.head, *r=rhs.head;l;l=l->next,r=r->next)
            {
                assert(l);
                assert(r);
                if( ! Pattern::AreEqual(*l,*r) ) return false;
            }

            return true;
        }


    }

}

#include "y/jive/pattern/basic/single.hpp"
#include "y/jive/pattern/basic/range.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Logic & Logic:: operator<<(const uint8_t b)
        {
            pushTail( new Single(b) );
            return *this;
        }

        Logic & Logic:: operator<<(const Within w)
        {
            pushTail( new Range(w) );
            return *this;
        }

    }

}

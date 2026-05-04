
#include "y/jive/pattern/logic/logic.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"
#include "y/format/decimal.hpp"
#include "y/pointer/auto.hpp"

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

        OutputStream & Logic:: emitLink(OutputStream &fp) const
        {
            unsigned i=1;
            for(const Pattern *p=head;p;p=p->next,++i)
            {
                p->viz(fp);
                to(p,fp) << '[';
                Label(fp,Decimal(i).c_str());
                Endl(fp << ']');
            }
            return fp;
        }

        void Logic:: optimizePatterns()
        {
            Patterns ops;
            while(size)
                ops.pushTail( popHead()->optimized() );
            swapForList(ops);
        }

        void Logic:: noMultiple() noexcept
        {
            Patterns ops;
            while(size)
            {
                AutoPtr<Pattern> rhs = popHead();
                for(const Pattern *lhs = ops.head;lhs;lhs=lhs->next)
                {
                    if( AreEqual(*lhs,*rhs) ) goto DONE;
                }

                ops.pushTail(rhs.yield());

            DONE:
                continue;
            }

        }

        void Logic:: stripBasic(Patterns &basic) noexcept
        {
            assert(0==basic.size);
            Patterns other;
            while(size)
            {
                Pattern * const p = popHead();
                if(p->isBasic())
                {
                    basic.pushTail(p);
                }
                else
                {
                    other.pushTail(p);
                }
            }
            swapForList(other);
        }


        void Logic:: alterBasic()
        {
            Patterns blist;
            {
                Patterns basic;
                stripBasic(basic);
                groupBasic(blist,basic);
            }
            mergeHead(blist);
        }



    }

}

#include "y/jive/pattern/basic/byte.hpp"
#include "y/jive/pattern/basic/lump.hpp"
#include "y/jive/pattern/leading.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Logic & Logic:: operator<<(const uint8_t b)
        {
            pushTail( new Byte(b) );
            return *this;
        }

        Logic & Logic:: operator<<(const Within w)
        {
            pushTail( w.create() );
            return *this;
        }

       

    }

}

#include "y/jive/pattern/leading.hpp"

namespace Yttrium
{
    namespace Jive
    {
        static inline void AddBasic(const Within &w, void * const args)
        {
            assert(args);
            Patterns &list = *static_cast<Patterns *>(args);
            list.pushTail(w.create());
        }

        void Logic:: groupBasic(Patterns &list, const Patterns &basic)
        {
            // collect leading chars
            Leading leading;
            for(const Pattern *p=basic.head;p;p=p->next)
            {
                assert(p->isBasic());
                p->glean(leading);
            }

            // create optimized basic list
            leading.forEach(AddBasic,&list);
        }
    }
}

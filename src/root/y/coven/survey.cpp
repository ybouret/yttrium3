
#include "y/coven/survey.hpp"
#include "y/format/decimal.hpp"
#include "y/string/format.hpp"
#include "y/core/max.hpp"
#include <iomanip>
#include "y/pointer/auto.hpp"

namespace Yttrium
{

    namespace Coven
    {
        //bool Survey::Trace = false;

        Survey:: Survey(const size_t nmin) noexcept :
        Proxy<const Vectors>(),
        list(),
        sampling(0),
        min_ncof( Max<size_t>(1,nmin) )
        {
        }

        Survey:: ~Survey() noexcept
        {
        }

        const Vectors & Survey:: locus() const noexcept { return list; }


        bool Survey:: got(const Vector &v) const noexcept
        {
            for(const Vector *node=list.head;node;node=node->next)
            {
                assert( node->size() == v.size() );
                if(v == *node) return true;
            }
            return false;
        }


        bool Survey:: insert(const Vector &v)
        {
            ++Coerce(sampling);
            if(v.ncof<min_ncof)  return false;
            if(got(v))           return false;
            if(!takes(v))        return false;
            place( new Vector(v) );
            return true;
        }


        Survey & Survey:: operator<< (const Vector &v)
        {
            (void) insert(v);
            return *this;
        }

        void Survey:: place(Vector *const newVector) noexcept
        {
            assert(newVector);
            Vector * const node = list.pushTail( newVector );
            while(node->prev && Vector::Compare(*(node->prev),*node) == Positive )
                list.towardsHead(node);
        }


        void Survey:: fusion(Survey &source) noexcept
        {
            assert(source.min_ncof==min_ncof);
            if( &source != this )
            {
                while( source.list.size )
                {
                    AutoPtr<Vector> pv = source.list.popHead(); assert( takes(*pv) );
                    if( got(*pv) ) continue;
                    place( pv.yield() );
                }
                Coerce(sampling) += source.sampling;
                Coerce(source.sampling) = 0;
            }
        }

        void Survey:: release() noexcept
        {
            list.release();
            Coerce(sampling) = 0;
        }

        bool operator==(const Survey &lhs, const Survey &rhs)
        {
            if(lhs->size!=rhs->size) return false;

            for(const Vector *l=lhs->head, *r=rhs->head;l;l=l->next,r=r->next)
            {
                if(*l != *r) return false;
            }

            return true;
        }

        void Survey::Callback(const Vector &v, void * const args)
        {
            assert(args);
            *static_cast<Survey *>(args) << v;
        }

        void Survey:: print(std::ostream &os) const
        {
            size_t indx = 0;
            for(const Vector *v=list.head;v;v=v->next)
            {
                const String uid = Formatted::Get("v%s",Decimal(++indx).c_str());
                os << std::setw(6) << uid << " = " << *v << std::endl;
            }
        }

    }

}

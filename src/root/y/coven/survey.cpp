
#include "y/coven/survey.hpp"

namespace Yttrium
{

    namespace Coven
    {
        //bool Survey::Trace = false;

        Survey:: Survey() noexcept :
        Proxy<const Vectors>(),
        list(),
        sampling(0)
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
                if(v == *node) return true;
            }
            return false;
        }

        Survey & Survey:: operator<< (const Vector &v)
        {
            ++Coerce(sampling);

            if(v.ncof<=0) return *this;
            if(got(v))    return *this;
            if(!takes(v)) return *this;
            //std::cerr << "\t [+] " << v << std::endl;

            Vector * const node = list.pushTail( new Vector(v) );
            while(node->prev && Vector::Compare(*(node->prev),*node) == Positive )
                list.towardsHead(node);


            return *this;
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
    }

}

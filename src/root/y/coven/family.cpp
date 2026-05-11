
#include "y/coven/family.hpp"

namespace Yttrium
{

    namespace Coven
    {

        Family:: Family(VCache &vc) noexcept:
        Object(),
        Metrics(vc),
        Recyclable(),
        list(),
        pool(vc),
        wksp(0),
        quality( computeQuality(list.size) )
        {

        }

        Family:: Family( const Family & other) :
        Object(),
        Metrics(other),
        Proxy<const Vectors>(),
        Recyclable(),
        Logging(),
        list(),
        pool(other.pool),
        wksp(0),
        quality(other.quality)
        {
            try
            {
                for(const Vector *v=other.list.head;v;v=v->next)
                    Coerce(list).pushTail( pool.query(*v) );
            }
            catch(...) { free_(); throw; }
        }

        void Family:: free() noexcept
        {
            free_();
        }

        void Family:: free_() noexcept
        {
            Y_Lock(pool);
            while(list.size)
                pool.store( Coerce(list).popTail() );
            Coerce(quality) = computeQuality(list.size);
        }

        Family:: ~Family() noexcept
        {
            free_();
            if(wksp) { pool.store(wksp); Coerce(wksp) = 0; }
        }

        void Family:: grow(Vector * const v) noexcept
        {
            assert(v);
            assert(list.size<dimension);
            assert(v->ncof);
            assert(v->mod2>0);

#if !defined(NDEBUG)
            for(const Vector *mine=list.head;mine;mine=mine->next)
            {
                assert(0 == mine->dot(*v) );
            }
#endif // !defined(NDEBUG)

            Coerce(list).pushTail(v);                    // update list
            Coerce(quality) = computeQuality(list.size); // update qualitt

            // put new vector into place for unique family
            while(v->prev && Vector::Compare(*(v->prev),*v) == Positive )
                Coerce(list).towardsHead(v);

        }

        Vector * Family:: acceptedFrom(const Vector * V,
                                       Vector * const Q,
                                       size_t & required)
        {
            assert(Q);
            assert(1==required);
            while(V)
            {
                ++required;
                Vector &Qnew = getWorkspace();
                if(!V->keepOrtho(Qnew,*Q))
                {
                    pool.store(Q);
                    return 0;
                }

                Q->exchange(Qnew);
                V = V->next;
            }

            return Q;
        }

        Vector &Family:: getWorkspace()
        {
            return *(wksp ? wksp : ( Coerce(wksp) = pool.query()));
        }

        const Vectors & Family:: locus() const noexcept { return list; }
        

        bool operator==(const Family &lhs, const Family &rhs) noexcept
        {
            assert(lhs.dimension==rhs.dimension);
            if(lhs.list.size!=rhs.list.size) return false;

            for(const Vector *l=lhs.list.head, *r=rhs.list.head;l;l=l->next,r=r->next)
            {
                if(*l != *r) return false;
            }

            return true;

        }
    }

}

#include "y/xml/log.hpp"
#include "y/xml/element.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{

    namespace Coven
    {

        void Family:: toXML(XML::Log &xml) const
        {
            const size_t       size = list.size;
            const char * const qlty = HumanReadableQuality(quality);
            Y_XML_Element_Attr(xml,Family,Y_XML_Attr(size) << Y_XML_Attr(dimension) << Y_XML_Attr(qlty));

            size_t i = 1;
            for(const Vector *v=list.head;v;v=v->next)
            {
                Y_XMLog(xml,"v" << i++ << " = " << *v);
            }
        }

    }

}


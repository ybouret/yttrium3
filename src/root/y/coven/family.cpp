
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
        quality( computeQuality(list.size) ),
        next(0),
        prev(0)
        {

        }

        Family:: Family( const Family & other) :
        Object(),
        Metrics(other),
        Recyclable(),
        list(),
        pool(other.pool),
        quality(other.quality),
        next(0),
        prev(0)
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
        }

        void Family:: grow(Vector * const v) noexcept
        {
            assert(v);
            assert(list.size<dimension);
            assert(v->ncof);
            assert(v->mod2>0);

            Coerce(list).pushTail(v);
            Coerce(quality) = computeQuality(list.size);

            while(v->prev && Vector::Compare(*(v->prev),*v) != Positive )
                Coerce(list).towardsHead(v);

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
            for(const Vector *v=list.head;v;v=v->next)
            {
                Y_XMLog(xml,*v);
            }
        }

    }

}


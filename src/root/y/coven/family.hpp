
//! \file

#ifndef Y_Coven_Family_Included
#define Y_Coven_Family_Included 1

#include "y/coven/vcache.hpp"
#include "y/ability/logging.hpp"

namespace Yttrium
{

    namespace Coven
    {
        class Family :
        public Object,
        public Metrics,
        public Recyclable,
        public Logging
        {
        public:
            explicit Family(VCache &vc) noexcept;
            virtual ~Family()           noexcept;
            Family(const Family &);

            virtual void free() noexcept;
            virtual void toXML(XML::Log &) const;

            template <typename READABLE>
            Vector * accepted(READABLE &a)
            {
                switch(quality)
                {
                    case Degenerate:
                        assert(0==list.size);
                        return acceptedFirst(a);

                    case TotalSpace:
                        assert(dimension==list.size);
                        return 0;

                    case Fragmental:
                    case HyperPlane:
                        break;
                }

                assert(list.size>0);
                assert(list.size<dimension);

                return 0;
            }

            void grow(Vector * const v) noexcept;



            const Vectors  list;
            VCache       & pool;
            const Quality  quality;
            Family *       next;
            Family *       prev;

        private:
            Y_Disable_Assign(Family);
            void free_() noexcept;

            template <typename READABLE> inline
            Vector * acceptedFirst( READABLE &a )
            {
                Vector * const v = pool.query();
                try
                {
                    if( v->ld(a) )
                        return v;
                    else {
                        pool.store(v);
                        return 0;
                    }
                } catch(...) { pool.store(v); throw; }
            }
        };
    }

}

#endif // !Y_Coven_Family_Included

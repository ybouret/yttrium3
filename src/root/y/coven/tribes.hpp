
//! \file

#ifndef Y_Coven_Tribes_Included
#define Y_Coven_Tribes_Included 1

#include "y/coven/tribe.hpp"

namespace Yttrium
{
    namespace Coven
    {

        class Tribes : public Proxy< const Tribe::List >, public Logging
        {
        public:
            template <typename T> inline
            explicit Tribes(const Matrix<T> & mu,
                            VCache          & vc,
                            const RowCache  & rc) :
            hired(0),
            ready(0),
            list()
            {
                const size_t nr = mu.rows;
                if(nr>0)
                {
                    Coerce(hired) = 1;
                    Coerce(ready) = nr - hired;
                    for(size_t i=mu.rows;i>0;--i)
                    {
                        list.pushHead( new Tribe(mu,i,vc,rc) );
                        assert(list.head->hired->size() == hired);
                        assert(list.head->ready->size()   == ready);
                    }
                }
            }

            virtual ~Tribes() noexcept;

            template <typename T> inline
            size_t generate(const Matrix<T> &mu)
            {
                std::cerr << "-- generating" << std::endl;
                if(ready<=0)
                {
                    list.release();
                    return 0;
                }
                else
                {
                    Tribe::List lineage;

                    for(const Tribe *tr=list.head;tr;tr=tr->next)
                    {
                        assert(tr->hired->size() == hired);
                        assert(tr->ready->size() == ready);
                        for(size_t id=1;id<=ready;++id)
                        {
                            lineage.pushTail( new Tribe(*tr,mu,id) );
                        }
                    }
                    list.swapForList(lineage);

                    ++Coerce(hired);
                    --Coerce(ready);

                    return list.size;
                }
            }

            virtual void toXML(XML::Log &) const;

            const size_t hired;
            const size_t ready;

        private:
            Y_Disable_Copy_And_Assign(Tribes);
            virtual const Tribe::List & locus() const noexcept;

            Tribe::List list;
        };

    }
}

#endif // !Y_Coven_Tribes_Included


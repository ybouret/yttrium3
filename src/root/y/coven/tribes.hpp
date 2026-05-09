
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
            static const unsigned NoMultiple = 0x01;
            static const unsigned HyperPlane = 0x01;


            //! initialize to rows!/(rows-1)! = rows possibilites
            /**
             \param mu matrix with rows to test
             \param vc vector cache
             \param rc row indices cache
             */
            template <typename T> inline
            explicit Tribes(const Matrix<T> & mu,
                            VCache          & vc,
                            const RCache    & rc,
                            Tribe::Callback   proc=0,
                            void * const      args=0) :
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
                        list.pushHead( new Tribe(mu,i,vc,rc,proc,args) );
                        assert(list.head->hired->size() == hired);
                        assert(list.head->ready->size()   == ready);
                    }
                }
            }

            virtual ~Tribes() noexcept; //!< cleanup


            //! new generation
            /**
             \param mu original matrix (hired+ready==mu.rows)
             \return at most mu.rows!/(mu.rows-hired)! possibilites
             */
            template <typename T> inline
            size_t generate(const Matrix<T> & mu,
                            const unsigned    strategy,
                            Tribe::Callback   proc=0,
                            void * const      args=0)
            {
                assert(hired+ready==mu.rows);
                if(ready<=0)
                {
                    list.release();
                    return 0;
                }
                else
                {
                    const apn maxCount = apn::Arrange(hired+ready,hired+1);
                    std::cerr << "-- generating at most " << maxCount << std::endl;
                    Tribe::List lineage;

                    for(const Tribe *tr=list.head;tr;tr=tr->next)
                    {
                        assert(tr->hired->size() == hired);
                        assert(tr->ready->size() == ready);
                        for(size_t id=1;id<=ready;++id)
                        {
                            lineage.pushTail( new Tribe(*tr,mu,id,proc,args) );
                        }
                    }
                    list.swapForList(lineage);

                    ++Coerce(hired);
                    --Coerce(ready);

                    if(strategy&NoMultiple) noMultiple();

                    std::cerr << "           generated: " << list.size << std::endl;
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
            void noMultiple() noexcept;
            
        };

    }
}

#endif // !Y_Coven_Tribes_Included


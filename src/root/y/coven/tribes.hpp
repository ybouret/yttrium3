
//! \file

#ifndef Y_Coven_Tribes_Included
#define Y_Coven_Tribes_Included 1

#include "y/coven/tribe.hpp"

namespace Yttrium
{
    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Tribes and lineage generation
        //
        //
        //______________________________________________________________________
        class Tribes : public Proxy< const Tribe::List >, public Logging
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned Precompile = 0x01; //!< remove zero vectors
            static const unsigned NoMultiple = 0x02; //!< remove multiple same families
            static const unsigned HyperPlane = 0x04; //!< only one next vector

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! initialize to rows!/(rows-1)! = rows possibilites
            /**
             \param mu   matrix with rows to test
             \param vc   vector cache
             \param rc   row indices cache
             \param proc optional proc for new vector
             \param args optional args for proc
             */
            template <typename T> inline
            explicit Tribes(const Matrix<T> & mu,
                            const unsigned    strategy,
                            VCache          & vc,
                            const RCache    & rc,
                            Tribe::Callback   proc=0,
                            void * const      args=0) :
            list(),
            indx(rc)
            {
                const size_t nr  = mu.rows;
                const bool   pre = 0 != (strategy&Precompile);
                if(nr>0)
                {

                    for(size_t i=mu.rows;i>0;--i)
                    {
                        Tribe * const tr = list.pushHead( new Tribe(mu,i,vc,rc,proc,args) );
                        if(0==tr->family->size)
                        {
                            std::cerr << "Null '" << mu[i] << "'" << std::endl;
                            if(pre)
                                indx << i;
                        }
                    }
                    if(pre) precompile();
                }
            }

            virtual ~Tribes() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void toXML(XML::Log &) const;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

#if 0
            //! new generation
            /**
             \param mu       original matrix (hired+ready==mu.rows)
             \param strategy optimization strategy
             \param proc     optional proc for new vector
             \param args     optional args for proc
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
#endif

            //! new generation
            /**
             \param mu       original matrix (hired+ready==mu.rows)
             \param strategy optimization strategy
             \param proc     optional proc for new vector
             \param args     optional args for proc
             \return new generation size
             */
            template <typename T> inline
            size_t generate(const Matrix<T> & mu,
                            const unsigned    strategy,
                            Tribe::Callback   proc=0,
                            void * const      args=0)
            {
                Tribe::List lineage;


                for(const Tribe *tr=list.head;tr;tr=tr->next)
                {
                    for(size_t i=tr->ready->size();i>0;--i)
                    {

                        Tribe * const clan = lineage.pushTail( new Tribe(*tr,mu,i,proc,args) );
                        if(!clan->last)
                        {
                            // mu[clan->irow] is null or included in sub-space
                            if( IsNullVector(mu[clan->irow]) )
                            {
                                std::cerr << "mu[" << clan->irow << "] is null" << std::endl;
                            }
                        }
                    }

                }
                list.swapForList(lineage);

                if(strategy&NoMultiple) noMultiple();
                return list.size;
            }

            template <typename ARRAY>
            static inline bool IsNullVector( ARRAY &arr )
            {
                for(size_t i=arr.size();i>0;--i) if( 0 != arr[i] ) return false;
                return true;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

        private:
            Tribe::List list;                  //!< current list of tribe
            RList       indx;                  //!< auxiliary indices
            Y_Disable_Copy_And_Assign(Tribes); //!< discarded
            virtual const Tribe::List & locus() const noexcept;

            void precompile() noexcept;
            void noMultiple() noexcept; //!< remove exact same families

        };

    }
}

#endif // !Y_Coven_Tribes_Included



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
            static const unsigned Precompile = 0x01; //!< remove initial zero vectors
            static const unsigned NoMultiple = 0x02; //!< remove multiple same families
            static const unsigned NoColinear = 0x04; //!< drop colinear vectors when found
            static const unsigned HyperPlane = 0x08; //!< only one next vector

            //! compute max generated tribes
            /**
             sum_{k=1}^n n!/(n-k)! = n! sum_{k=0}^{n-1} 1/k! approx e * n!
             \param n number of rows
             \return sum_{k=1}^n n!/(n-k)!
             */
            static apn MaxGenerated(const size_t n)
            {
                apn sum = 0;
                for(size_t k=1;k<=n;++k) sum += apn::Arrange(n,k);
                return sum;
            }

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! initialize to rows!/(rows-1)! = rows possibilites
            /**
             \param mu        matrix with rows to test
             \param strategy  optimization strategy
             \param vc        vector cache
             \param rc        row indices cache
             \param proc      optional proc for new vector
             \param args      optional args for proc
             */
            template <typename T> inline
            explicit Tribes(const Matrix<T> & mu,
                            const unsigned    strategy,
                            VCache          & vc,
                            const RCache    & rc,
                            Tribe::Callback   proc=0,
                            void * const      args=0) :
            list(),
            cycle(0)
            {
                RSet         zset(rc);
                const size_t nr            = mu.rows;
                const bool   usePrecompile = 0 != (strategy&Precompile);
                if(nr>0)
                {

                    for(size_t i=mu.rows;i>0;--i)
                    {
                        Tribe * const tr = list.pushHead( new Tribe(mu,i,vc,rc,proc,args) );
                        if(usePrecompile && 0==tr->family->size)
                            zset << i;
                    }
                    if(usePrecompile) precompile(zset);
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
                const bool useNoColinear = 0!=(strategy & NoColinear);
                const bool useHyperPlane = 0!=(strategy & HyperPlane);
                ++Coerce(cycle);
                {
                    Tribe::List lineage;
                    for(Tribe *oldTribe=list.head;oldTribe;oldTribe=oldTribe->next)
                    {

                        switch(oldTribe->family.quality)
                        {
                            case Family::TotalSpace: continue; // no more new vector
                            case Family::Degenerate: break;
                            case Family::Fragmental: break;
                            case Family::HyperPlane:
                                if(useHyperPlane)
                                {
                                    std::cerr << "should use HyperPlane with " << oldTribe->hired << " | " << oldTribe->ready << std::endl;
                                }
                                break;
                        }

                        //------------------------------------------------------
                        //
                        // create a new tribe for each ready index
                        //
                        //------------------------------------------------------
                        const RList &rlist = *(oldTribe->ready);
                        for(size_t id=1;id<=rlist->size;)
                        {
                            Tribe * const newTribe = lineage.pushTail( new Tribe(*oldTribe,mu,id,proc,args) );
                            assert(newTribe);
                            assert(newTribe->ready->size()+1==oldTribe->ready->size());

                            //--------------------------------------------------
                            // check if necessary to post-process
                            //--------------------------------------------------
                            if(!NoColinear || newTribe->last) { ++id; continue; }

                            //--------------------------------------------------
                            // row that led to a zero vector (null or colinear)
                            //--------------------------------------------------
                            const size_t zr = newTribe->irow;
                            assert(newTribe->hired.contains(zr));
                            assert(oldTribe->ready.contains(zr));
                            assert(oldTribe->ready[id]==zr);

                            //--------------------------------------------------
                            // update oldTribe:
                            // shorten rlist => no increase of id
                            //--------------------------------------------------
                            const RSet hired(oldTribe->hired);
                            oldTribe->demote(zr); assert(oldTribe->hired.contains(zr));

                            //--------------------------------------------------
                            // check if zero vector
                            //--------------------------------------------------
                            if( IsNullVector(mu[zr]) ) {

                                //std::cerr << "mu[" << zr << "] is null" << std::endl;
                                DemoteForward(oldTribe->next,zr); // propagate to future  tribes
                                DemoteReverse(newTribe->prev,zr); // propagate to created tribes
                                continue;
                            }

                            //--------------------------------------------------
                            // mu[zr] was in oldTribe sub-space:
                            // if zr is hired, mu[zr] will produce zero
                            //--------------------------------------------------
                            assert(newTribe->nreq>0);
                            if(useNoColinear)
                            {
                                //std::cerr << "mu[" << zr << "]=" << mu[zr] << " is dependent of " << hired << std::endl;
                                DemoteForward(oldTribe->next,hired,zr); // propagate to future  tribes
                                DemoteReverse(newTribe->prev,hired,zr); // propagate to created tribes
                            }


                        }

                    }
                    //--------------------------------------------------------------
                    //
                    //
                    // Leave: loop over old tribes
                    //
                    //
                    //--------------------------------------------------------------
                    list.swapForList(lineage);
                }


                if(0!=(strategy&NoMultiple)) noMultiple();
                return list.size;
            }


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

        private:
            Tribe::List list;                  //!< current list of tribe
            Y_Disable_Copy_And_Assign(Tribes); //!< discarded
            virtual const Tribe::List & locus() const noexcept;

            void precompile(const RSet &) noexcept; //!< remove zero vector before start
            void noMultiple() noexcept; //!< remove exact same families

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

            template <typename ARRAY> static inline bool IsNullVector( ARRAY &arr )
            {
                for(size_t i=arr.size();i>0;--i) if( 0 != arr[i] ) return false;
                return true;
            }


            static void DemoteForward(Tribe * curr, const size_t zr) noexcept;
            static void DemoteReverse(Tribe * curr, const size_t zr) noexcept;

            static void DemoteForward(Tribe * curr, const RSet &hired, const size_t zr) noexcept;
            static void DemoteReverse(Tribe * curr, const RSet &hired, const size_t zr) noexcept;

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        public:
            const size_t cycle; //!< current cycle
        };

    }
}

#endif // !Y_Coven_Tribes_Included


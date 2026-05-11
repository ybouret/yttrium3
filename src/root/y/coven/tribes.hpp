
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
            static const unsigned RunTimeGTZ = 0x02; //!< remove zero vectors at run time
            static const unsigned NoMultiple = 0x04; //!< remove multiple same families
            static const unsigned NoColinear = 0x08; //!< drop colinear vectors when found
            //static const unsigned HyperPlane = 0x04; //!< only one next vector

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
            zset(rc),
            cycle(0)
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

                            if(pre) {
                                std::cerr << "\tnull#" << i << std::endl;
                                zset << i;
                            }
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
                const bool useRunTimeGTZ = 0!=(strategy & RunTimeGTZ);
                const bool useNoColinear = 0!=(strategy & NoColinear);
                const bool useNullVector = useRunTimeGTZ || useNoColinear;
                const bool useAllVectors = !useNullVector;

                //std::cerr << "strategy     =" << strategy << std::endl;
                //std::cerr << "usePrecompile=" << usePrecompile << std::endl;
                //std::cerr << "useNoColinear=" << useNoColinear << std::endl;
                //std::cerr << "useNullVector=" << useNullVector << std::endl;
                //std::cerr << "useAllVectors=" << useAllVectors << std::endl;


                ++Coerce(cycle);
                //std::cerr << "-- generate cycle #" << cycle << std::endl;
                //--------------------------------------------------------------
                //
                //
                // ENTER: loop over old tribes
                //
                //
                //--------------------------------------------------------------
                {
                    Tribe::List lineage;
                    for(Tribe *oldTribe=list.head;oldTribe;oldTribe=oldTribe->next)
                    {
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
                            if(useAllVectors || newTribe->last) { ++id; continue; }
                            assert(useRunTimeGTZ ||useNoColinear);

                            //--------------------------------------------------
                            // row that led to a zero vector (null or colinear)
                            //--------------------------------------------------
                            const size_t zr = newTribe->irow;
                            assert(newTribe->hired->found(zr));
                            assert(oldTribe->ready->found(zr));
                            assert(oldTribe->ready[id]==zr);

                            //--------------------------------------------------
                            // update oldTribe:
                            // shorten rlist => no increase of id
                            //--------------------------------------------------
                            oldTribe->demote(zr); assert(oldTribe->hired->found(zr));

                            //--------------------------------------------------
                            // check if zero vector
                            //--------------------------------------------------
                            if( IsNullVector(mu[zr]) ) {

                                std::cerr << "mu[" << zr << "] is null" << std::endl;
                                if(useRunTimeGTZ)
                                {
                                    demote( oldTribe->next,zr); // propagate to future  tribes
                                    rdemote(newTribe->prev,zr); // propagate to created tribes
                                }
                                continue;
                            }

                            //--------------------------------------------------
                            // mu[zr] was in oldTribe sub-space
                            //--------------------------------------------------
                            //std::cerr << "mu[" << zr << "] is dependent" << std::endl;

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


                if(strategy&NoMultiple) noMultiple();
                return list.size;
            }

            template <typename ARRAY>
            static inline bool IsNullVector( ARRAY &arr )
            {
                for(size_t i=arr.size();i>0;--i) if( 0 != arr[i] ) return false;
                return true;
            }

            static inline void demote(Tribe * curr, const size_t zr) noexcept
            {
                while(curr)
                {
                    curr->demote(zr);
                    curr=curr->next;
                }
            }

            static inline void rdemote(Tribe * curr, const size_t zr) noexcept
            {
                while(curr)
                {
                    curr->demote(zr);
                    curr=curr->prev;
                }

            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

        private:
            Tribe::List list;                  //!< current list of tribe
            RSet        zset;                  //!< auxiliary
            Y_Disable_Copy_And_Assign(Tribes); //!< discarded
            virtual const Tribe::List & locus() const noexcept;

            void precompile() noexcept;
            void noMultiple() noexcept; //!< remove exact same families
        public:
            const size_t cycle;
        };

    }
}

#endif // !Y_Coven_Tribes_Included


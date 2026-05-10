
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
            static const unsigned PostFusion = 0x04;
            //static const unsigned HyperPlane = 0x04; //!< only one next vector

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
            zset(rc)
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
                                zset << i;
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
                Tribe::List lineage;
                zset.free();

                //--------------------------------------------------------------
                //
                //
                // ENTER: loop over old tribes
                //
                //
                //--------------------------------------------------------------
                for(Tribe *oldTribe=list.head;oldTribe;oldTribe=oldTribe->next)
                {
                    std::cerr << "process tribe..." << std::endl;
                    //----------------------------------------------------------
                    //
                    // create a new tribe for each ready index
                    //
                    //----------------------------------------------------------
                    Tribe::List  clan;
                    const RList &rlist = *(oldTribe->ready);
                    for(size_t id=1;id<=rlist->size;++id)
                    {
                        Tribe * const newTribe = clan.pushTail( new Tribe(*oldTribe,mu,id,proc,args) );
                        assert(newTribe);
                        assert(newTribe->ready->size()+1==oldTribe->ready->size());
                        if(!newTribe->last)
                        {
                            // zr = oldTribe->ready[id]
                            const size_t zr = newTribe->irow;
                            assert(newTribe->hired->found(zr));
                            assert(oldTribe->ready->found(zr));
                            assert(oldTribe->ready[id]==zr);
                            std::cerr << "mu[" << zr << "] = " << mu[zr];
                            if( IsNullVector(mu[zr]) )
                            {
                                std::cerr << " is null" << std::endl;
                                if(zset->found(zr))
                                {
                                    std::cerr << "multiple " << zr << std::endl;
                                }
                                zset << zr;
                                // demote everywhere
                                rdemote(newTribe->prev,zr);
                                demote(lineage.head,zr);
                                demote(oldTribe->next,zr);
                            }
                            else
                            {
                                std::cerr << " is included in vector space " << (oldTribe->hired) << std::endl;
                            }

                        }
                    }
                    lineage.mergeTail(clan);
                    //--------------------------------------------------------------
                    //
                    //
                    // Leave: loop over old tribes
                    //
                    //
                    //--------------------------------------------------------------
                }
                list.swapForList(lineage);

                std::cerr << "-- zset = " << zset << std::endl;

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

        };

    }
}

#endif // !Y_Coven_Tribes_Included


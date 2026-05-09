
//! \file

#ifndef Y_Coven_Tribe_Included
#define Y_Coven_Tribe_Included 1

#include "y/coven/family.hpp"
#include "y/container/matrix.hpp"
#include "y/handy/joint/set.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/stream/xmlog.hpp"

namespace Yttrium
{

    namespace Coven
    {

        typedef Handy::JointSet<const size_t,MultiThreadedObject> RSet;   //!< alias
        typedef RSet::ListType                                    RList;  //!< alias
        typedef RSet::CacheType                                   RCache; //!< alias
        typedef RList::NodeType                                   RNode;  //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Tribe for a given set of rows
        //
        //
        //______________________________________________________________________
        class Tribe : public Object, public Logging
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxListOf<Tribe> List; //!< alias
            typedef void (*Callback)(const Vector &, void * const); //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param mu matrix of rows
             \param ir master index
             \param vc vector cache
             \param rc row index cache
             \param proc optional proc for new vector
             \param args optional args for proc
             */
            template <typename T>
            explicit Tribe(const Matrix<T> & mu,
                           const size_t      ir,
                           VCache          & vc,
                           const RCache    & rc,
                           Callback          proc=0,
                           void * const      args=0) :
            family(vc),
            hired(rc),
            ready(rc),
            last(0),
            next(0),
            prev(0)
            {
                assert(ir>=1);
                assert(ir<=mu.rows);
                assert(mu.cols==family.dimension);
                setup(ir,mu.rows);
                assert(hired->size()+ready->size()==mu.rows);
                process(mu[ir],proc,args);
            }

            //! expand
            /**
             \param tr parent tribe
             \param mu matrix of rows
             \param id index to extract in ready
             \param proc optional proc for new vector
             \param args optional args for proc
             */
            template <typename T> inline
            Tribe(const Tribe     &tr,
                  const Matrix<T> &mu,
                  const size_t     id,
                  Callback          proc=0,
                  void * const      args=0) :
            family(tr.family),
            hired(tr.hired),
            ready(tr.ready),
            last(0),
            next(0),
            prev(0)
            {
                assert(id>=1); assert(id<=ready->size());
                RNode * const node = Coerce(ready).extract(id);
                Coerce(hired).insert(node);
                const size_t    ir   = **node;
                process(mu[ir],proc,args);
            }

            virtual ~Tribe() noexcept;

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
            // Members
            //
            //__________________________________________________________________
            const Family         family; //!< current family
            const RSet           hired;  //!< set of hired rows
            const RSet           ready;  //!< list of ready rows
            const Vector * const last;   //!< last added vector
            Tribe *              next;   //!< for list
            Tribe *              prev;   //!< for list

        private:
            Y_Disable_Copy_And_Assign(Tribe); //!< discarded

            //! prepare hired and ready
            /**
             \param ir row index
             \param nr mu.rows
             */
            void setup(const size_t ir, const size_t nr);

            //! try to accept a new vector, then processed
            /**
             \param arr  compatible array
             \param proc optional proc for new vector
             \param args optional args for proc
             */
            template <typename ARRAY> inline
            void process( ARRAY &arr, Callback proc, void * const args)
            {
                Vector * const v = Coerce(family).accepted(arr);
                if(v)
                {
                    assert(v->ncof>0);
                    Coerce(family).grow(v);
                    Coerce(last) = v;
                    if(proc) proc(*v,args);
                }
            }


        };

    }

}

#endif // !Y_Coven_Tribe_Included


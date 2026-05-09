
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

        typedef Handy::JointSet<const size_t,MultiThreadedObject> RowSet;   //!< alias
        typedef RowSet::ListType                                  RowList;  //!< alias
        typedef RowSet::CacheType                                 RowCache; //!< alias
        typedef RowList::NodeType                                 RowNode;  //!< alias

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
            typedef CxxListOf<Tribe> List;
            
            //! setup
            /**
             \param mu matrix of rows
             \param ir master index
             \param vc vector cache
             \param rc row index cache
             */
            template <typename T>
            explicit Tribe(const Matrix<T> & mu,
                           const size_t      ir,
                           VCache          & vc,
                           const RowCache  & rc) :
            family(vc),
            hired(rc),
            ready(rc),
            last(0),
            next(0),
            prev(0),
            sigil(rc)
            {
                assert(ir>=1);
                assert(ir<=mu.rows);
                assert(mu.cols==family.dimension);
                setup(ir,mu.rows);
                assert(hired->size()+ready->size()==mu.rows);
                process(mu[ir]);
            }

            template <typename T> inline
            Tribe(const Tribe     &tr,
                  const Matrix<T> &mu,
                  const size_t     id) :
            family(tr.family),
            hired(tr.hired),
            ready(tr.ready),
            last(0),
            next(0),
            prev(0),
            sigil(tr.sigil)
            {
                assert(id>=1); assert(id<=ready->size());
                RowNode * const node = Coerce(ready).extract(id);
                Coerce(hired).insert(node);
                const size_t    ir   = **node;
                Coerce(sigil) << ir;
                process(mu[ir]);
            }

            virtual ~Tribe() noexcept;

            virtual void toXML(XML::Log &) const;



            const Family  family; //!< current family
            const RowSet  hired;  //!< set of hired rows
            const RowSet  ready;  //!< list of ready rows
            const Vector * const last; //!< last added vector
            Tribe *       next;   //!< for list
            Tribe *       prev;   //!< for list
            const RowList sigil;  //!< in-order used

        private:
            Y_Disable_Copy_And_Assign(Tribe); //!< discarded

            //! prepare hired and ready
            /**
             \param ir row index
             \param nr mu.rows
             */
            void setup(const size_t ir, const size_t nr);

            template <typename ARRAY> inline
            void process( ARRAY &arr )
            {
                Vector * const v = Coerce(family).accepted(arr);
                if(v)
                {
                    Coerce(family).grow(v);
                    Coerce(last) = v;
                }
            }


        };

    }

}

#endif // !Y_Coven_Tribe_Included



//! \file

#ifndef Y_Coven_Tribe_Included
#define Y_Coven_Tribe_Included 1

#include "y/coven/family.hpp"
#include "y/container/matrix.hpp"
#include "y/handy/joint/set.hpp"
#include "y/threading/multi-threaded-object.hpp"

namespace Yttrium
{

    namespace Coven
    {

        typedef Handy::JointSet<size_t,MultiThreadedObject> RowSet;   //!< alias
        typedef RowSet::ListType                            RowList;  //!< alias
        typedef RowSet::CacheType                           RowCache; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Tribe for a given set of rows
        //
        //
        //______________________________________________________________________
        class Tribe
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
            prev(0)
            {
                assert(ir>=1);
                assert(ir<=mu.rows);
                assert(mu.cols==family.dimension);
                setup(ir,mu.rows);
                assert(hired->size()+ready->size==mu.rows);

                Vector * first = Coerce(family).accepted(mu[ir]);
                if(first)
                {
                    Coerce(last) = first;
                    Coerce(family).grow(first);
                }
            }

            template <typename T> inline
            Tribe(const Tribe     &tribe,
                  const Matrix<T> &mu,
                  const size_t     roll) :
            family(tribe.family),
            hired(tribe.hired),
            ready(tribe.ready),
            last(0),
            next(0),
            prev(0)
            {
                assert(roll<ready->size);
                assert(hired->size()+ready->size==mu.rows);
                Coerce(ready)->rollTailToHead();
                const size_t ir = ready.head(); assert(ir>=1); assert(ir<=mu.rows); assert( !hired->found(ir) );
                Coerce(hired).insert(Coerce(ready)->popHead());

                Vector * const v = Coerce(family).accepted(mu[ir]);
                if(v)
                {
                    Coerce(family).grow(v);
                    Coerce(last) = v;
                }
            }


            virtual ~Tribe() noexcept;



            const Family  family; //!< current family
            const RowSet  hired;  //!< set of hired rows
            const RowList ready;  //!< list of ready rows
            const Vector * const last; //!< last added vector
            Tribe *       next;   //!< for list
            Tribe *       prev;   //!< for list
            
        private:
            Y_Disable_Copy_And_Assign(Tribe); //!< discarded

            //! prepare hired and ready
            /**
             \param ir row index
             \param nr mu.rows
             */
            void setup(const size_t ir, const size_t nr);

        };

    }

}

#endif // !Y_Coven_Tribe_Included


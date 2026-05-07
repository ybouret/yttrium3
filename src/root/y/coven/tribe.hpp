
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

        typedef Handy::JointSet<size_t,MultiThreadedObject> RowSet;
        typedef RowSet::ListType                            RowList;
        typedef RowSet::CacheType                           RowCache;


        class Tribe
        {
        public:
            //! setup
            /**
             \param
             \param
             \param
             \param
             */
            template <typename T>
            explicit Tribe(const Matrix<T> & mu,
                           const size_t      ir,
                           VCache          & vc,
                           const RowCache  & rc) :
            family(vc),
            hired(rc),
            ready(rc),
            next(0),
            prev(0)
            {
                assert(ir>=1);
                assert(ir<=mu.rows);
                assert(mu.cols==family.dimension);
                setup(ir,mu.rows);

                Vector * first = Coerce(family).accepted(mu[ir]);
                if(first) Coerce(family).grow(first);
            }

            virtual ~Tribe() noexcept;
            


            const Family  family; //!< current family
            const RowSet  hired;  //!< set of hired rows
            const RowList ready;  //!< list of ready rows
            Tribe *       next;
            Tribe *       prev;
        private:
            Y_Disable_Assign(Tribe);
            void setup(const size_t ir, const size_t nr);

        };

    }

}

#endif // !Y_Coven_Tribe_Included


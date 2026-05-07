
//! \file

#ifndef Y_Coven_Tribes_Included
#define Y_Coven_Tribes_Included 1

#include "y/coven/tribe.hpp"

namespace Yttrium
{
    namespace Coven
    {

        class Tribes : public Proxy< const Tribe::List >
        {
        public:
            template <typename T> inline
            explicit Tribes(const Matrix<T> & mu,
                            VCache          & vc,
                            const RowCache  & rc)
            {
                for(size_t i=mu.rows;i>0;--i)
                    list.pushHead( new Tribe(mu,i,vc,rc) );
            }

            template <typename T> inline
            size_t generate(const Matrix<T> &mu)
            {
                Tribe::List lineage;
                for(const Tribe *tr=list.head;tr;tr=tr->next)
                {

                }
            }


            explicit Tribes() noexcept;
            virtual ~Tribes() noexcept;

            //const size_t level;

        private:
            Y_Disable_Copy_And_Assign(Tribes);
            virtual const Tribe::List & locus() const noexcept;

            Tribe::List list;
        };

    }
}

#endif // !Y_Coven_Tribes_Included


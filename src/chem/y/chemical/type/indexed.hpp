
//! \file

#ifndef Y_Chemical_Indexed_Included
#define Y_Chemical_Indexed_Included 1

#include "y/chemical/type/entity.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        enum Level
        {
            TopLevel,
            SubLevel,
            AuxLevel
        };

        class Indexed : public Entity
        {
        public:
            static const unsigned Levels = AuxLevel;

            explicit Indexed(const size_t);
            explicit Indexed(const String &,const size_t);
            virtual ~Indexed() noexcept;

            template <typename ARRAY> inline
            typename ARRAY::Type & operator()(ARRAY &arr, const Level L) const noexcept
            {
                assert(indx[L]>0); assert(indx[L]<=arr.size());
                return arr[ indx[L] ];
            }

            template <typename ARRAY> inline
            typename ARRAY::ConstType & operator()(const ARRAY &arr, const Level L) const noexcept
            {
                assert(indx[L]>0); assert(indx[L]<=arr.size());
                return arr[ indx[L] ];
            }



            const size_t indx[Levels];
            
        private:
            Y_Disable_Copy_And_Assign(Indexed);
            void setup(const size_t) noexcept;
        };

    }

}

#endif // !Y_Chemical_Indexed_Included


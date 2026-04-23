
//! \file

#ifndef Y_Memory_LegacyTroop_Included
#define Y_Memory_LegacyTroop_Included 1

#include "y/memory/troop.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Troop with operation on head
        //
        //
        //______________________________________________________________________
        template <typename T, typename OBJECT>
        class LegacyTroop : public Troop<T,OBJECT>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases
            typedef Troop<T,OBJECT> TroopType;
            using TroopType::size;
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit LegacyTroop(const size_t n) : TroopType(n)
            {
                Coerce(size) = n;
            }

            inline virtual ~ LegacyTroop() noexcept
            {
                Coerce(size) = 0;
            }



        private:
            Y_Disable_Copy_And_Assign(LegacyTroop);
        };

    }

}

#endif // !Y_Memory_LegacyTroop_Included

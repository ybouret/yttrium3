
//! \file

#ifndef Y_Chemical_Species_Included
#define Y_Chemical_Species_Included 1

#include "y/chemical/formula.hpp"
#include "y/chemical/type/indexed.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Species
        //
        //
        //______________________________________________________________________
        class Species :
        public CountedObject,
        public Formula,
        public Indexed
        {
        public:
           
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Species(const Formula &, const size_t); //!< setup
            virtual ~Species() noexcept;                     //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const int    z; //!< algebraic charge

        private:
            Y_Disable_Copy_And_Assign(Species); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Species_Included


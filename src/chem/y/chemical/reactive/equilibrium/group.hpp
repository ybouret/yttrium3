

//! \file

#ifndef Y_Chemical_Equilibrium_Group_Included
#define Y_Chemical_Equilibrium_Group_Included 1

#include "y/chemical/reactive/elist.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        
        //______________________________________________________________________
        //
        //
        //
        //! Group of connected equilibria
        //
        //
        //______________________________________________________________________
        class EGroup : public Object, public EList
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxListOf<EGroup> List; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit EGroup(Equilibrium &); //!< setup with first equilibrium
            virtual ~EGroup()     noexcept; //!< cleanup
            Y_OSTREAM_PROTO(EGroup);       //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool accepts(const Equilibrium &) const noexcept; //!< \return true iff connected
            void finalize() noexcept; //!< sort and relabel

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            EGroup * next; //!< for list
            EGroup * prev; //!< for list

        private:
            Y_Disable_Copy_And_Assign(EGroup); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Equilibrium_Group_Included

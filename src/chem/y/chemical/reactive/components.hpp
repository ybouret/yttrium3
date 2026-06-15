
//! \file

#ifndef Y_Chemical_Components_Included
#define Y_Chemical_Components_Included 1

#include "y/chemical/reactive/actors.hpp"
#include "y/chemical/type/assembly.hpp"
#include "y/ability/freezable.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        enum EqKind
        {
            Outlawed,
            ProdOnly,
            ReacOnly,
            BothWays
        };

        //______________________________________________________________________
        //
        //
        //
        //! Components (without constant)
        //
        //
        //______________________________________________________________________
        class Components : public Indexed, public Freezable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Components(const String &, const size_t); //!< setup
            virtual ~Components() noexcept;                    //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void  addReac(const unsigned, const Species &); //!< add new reactant
            void  addProd(const unsigned, const Species &); //!< add new product
            bool  electroneutral() const; //!< \return true iff electroneutral
            bool  atLeastOneItem() const; //!< \return true iff at least one item

            xreal_t massAction(const xreal_t, XMul &, const XReadable &, const Level) const; //!< \return mass action
            xreal_t massAction(const xreal_t, XMul &, const XReadable &, const Level, const xreal_t) const; //!< \return shifted mass action

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const EqKind   kind; //!< updated
            const Actors   reac; //!< reactant(s)
            const Actors   prod; //!< product(s)
            const xreal_t  one;  //!< numeric 1

        private:
            Y_Disable_Copy_And_Assign(Components);  //!< discarded
            void   checkUnused(const char * const, const Species &) const; //!< helper
            EqKind computeKind() const noexcept; //!< helper
        };

    }
}

#endif // !Y_Chemical_Components_Included


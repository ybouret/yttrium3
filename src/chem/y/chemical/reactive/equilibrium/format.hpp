
//! \file

#ifndef Y_Chemical_Equilibrium_Format_Included
#define Y_Chemical_Equilibrium_Format_Included 1

#include "y/chemical/reactive/equilibrium.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Helper to format equilibria
        //
        //
        //______________________________________________________________________
        class EqFormat
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit EqFormat()        noexcept; //!< setup
            virtual ~EqFormat()        noexcept; //!< cleanup
            EqFormat(const EqFormat &) noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! enroll all parts
            void enroll(const Equilibrium &) noexcept;

            //! pretty print
            /**
             \param os output stream
             \param eq equilibrium
             \param wK with K flag
             \param tK time to evaluate if necessary
             \return os
             */
            std::ostream & print(std::ostream      &os,
                                 const Equilibrium &eq,
                                 const bool         wK,
                                 const xreal_t      tK) const;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Assembly efmt; //!< for name
            const Assembly rfmt; //!< for reac
            const Assembly pfmt; //!< for prod

        private:
            Y_Disable_Assign(EqFormat); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Equilibrium_Format_Included



//! \file


#ifndef Y_Jive_Joker_Included
#define Y_Jive_Joker_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {
        

        //______________________________________________________________________
        //
        //
        //
        //! Joker Pattern interface
        //
        //
        //______________________________________________________________________
        class Joker : public Pattern
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit Joker(const uint32_t, const Motif &) noexcept; //!< setup
            Joker(const Joker &);                                   //!< duplicate by cloning

        public:
            virtual ~Joker() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void glean(Leading &) const noexcept;

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________

            //! \return true if identical patterns
            static bool HaveSameMotif(const Joker &, const Joker &) noexcept;
            OutputStream & emitLink(OutputStream &) const; //!< emit and link motif \return output stream

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Motif motif; //!< current motif

        protected:
            void optimizeMotif(); //!< change motif for its optimized form

        private:
            Y_Disable_Assign(Joker); //!< discarded

        };

    }


}

#endif // !Y_Jive_Joker_Included


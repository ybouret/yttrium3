//! \file

#ifndef Y_Chemical_Formula_Included
#define Y_Chemical_Formula_Included 1

#include "y/jive/syntax/xnode.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Jive::Syntax::XNode XNode; //!< alias
        typedef Jive::Syntax::XList XList; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Formula base class, wrapping a XNode
        //
        //
        //______________________________________________________________________
        class Formula_ : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            static Formula_ * Create(XNode * const); //!< \return safe new Formula_
            virtual          ~Formula_() noexcept;   //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            XNode * const code; //!< inner code

        private:
            Y_Disable_Copy_And_Assign(Formula_);       //!< discared
            explicit Formula_(XNode * const) noexcept; //!< setup
        };

        //______________________________________________________________________
        //
        //
        //
        //! (shared) Formula
        //
        //
        //______________________________________________________________________
        class Formula : public ArcPtr<Formula_>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definition
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Formula"
            class Translator;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Formula(XNode * const); //!< setup
            explicit Formula(const Formula &) noexcept; //!< duplicate
            virtual ~Formula() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String makeName(int * const = 0) const; //!< \return name, optional charge loading
            String makeHTML() const;                //!< \return html tag

        private:
            Y_Disable_Assign(Formula); //!< discarded
        };

    }
}

#endif // !Y_Chemical_Formula_Included


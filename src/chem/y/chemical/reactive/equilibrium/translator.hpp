
//! \file

#ifndef Y_Chemical_Equilibrium_Translator_Included
#define Y_Chemical_Equilibrium_Translator_Included 1

#include "y/chemical/reactive/equilibria.hpp"
#include "y/chemical/library.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/chemical/formula/translator.hpp"
#include "y/lua++/state.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Compile equilibrium
        //
        //
        //______________________________________________________________________
        class Equilibrium::Translator
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Translator(const Identifier &,const Lua::VM &); //!< setup
            virtual ~Translator() noexcept;                          //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! compile node
            void operator()(AutoPtr<XNode> &,
                            Library        &,
                            Equilibria     &);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Identifier lang; //!< identifier
            Lua::VM          lvm;  //!< lua if needed

        private:
            Y_Disable_Copy_And_Assign(Translator); //!< discarded

            //! helper
            void fill(Actor::List          &,
                      XNode * const         ,
                      Library              &,
                      const char * const);
        };
    }

}

#endif // !Y_Chemical_Equilibrium_Translator_Included


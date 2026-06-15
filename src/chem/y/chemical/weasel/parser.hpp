//! \file

#ifndef Y_Chemical_Weasel_Parser_Included
#define Y_Chemical_Weasel_Parser_Included 1

#include "y/chemical/weasel.hpp"
#include "y/jive/parser.hpp"

namespace Yttrium
{
    namespace Chemical
    {
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        //______________________________________________________________________
        //
        //
        //
        //! Weasel parser
        //
        //
        //______________________________________________________________________
        class Weasel :: Parser : public Jive::Parser
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Parser();          //!< setup
            virtual ~Parser() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Compound & formula;      //!< inner formula compound
            const Compound & equilibrium;  //!< inner equilibrium compound
            const Rule     & alias;        //!< inner alias terminal

        private:
            Y_Disable_Copy_And_Assign(Parser); //!< discarded
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
    }
}

#endif // !Y_Chemical_Weasel_Parser_Included


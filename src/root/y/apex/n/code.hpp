
//! \file

#ifndef Y_Apex_Natural_Code_Included
#define Y_Apex_Natural_Code_Included 1

#include "y/apex/natural.hpp"
#include "y/apex/k/keg.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //! system Keg setup
        struct _Keg
        {
            typedef uint32_t Word; //!< alias
            typedef uint64_t Core; //!< alias
        };

        typedef Keg<_Keg::Word> KegType; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! precomputed natural_t
        //
        //
        //______________________________________________________________________
        class PreComputed
        {
        public:
            typedef _Keg::Word Word; //!< alias

            //! setup \param n integral value
            inline PreComputed(const natural_t n) noexcept :
            value(n),
            wksp(n),
            words(0),
            word( Calculus::SplitWord::Make<Word>::From( Coerce(wksp), Coerce(words)))
            {
            }

            //! cleanup
            inline ~PreComputed() noexcept {}

            const natural_t    value; //!< original value
            const natural_t    wksp;  //!< value as workdpace
            const size_t       words; //!< number of words
            const Word * const word;  //!< array of words

        private:
            Y_Disable_Copy_And_Assign(PreComputed); //!< discarded
        };

    }

}
#endif // !Y_Apex_Natural_Code_Included



//! \file

#ifndef Y_Jive_Pattern_Dictionary_Included
#define Y_Jive_Pattern_Dictionary_Included 1

#include "y/jive/pattern.hpp"
#include "y/container/associative/suffix/map.hpp"

namespace Yttrium
{
    namespace Jive
    {

        typedef SuffixMap<String,const Motif> DictMap; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Dictionary of compiled patterns
        //
        //
        //______________________________________________________________________
        class Dictionary : public DictMap
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Dictionary();          //!< setup emptu
            Dictionary(const Dictionary&);  //!< duplicate
            virtual ~Dictionary() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void operator()(const String &,      Pattern * const); //!< insert a new key/pattern
            void operator()(const char * const , Pattern * const); //!< insert a new key/pattern

            Pattern * clone(const String &);



        private:
            Y_Disable_Assign(Dictionary); //!< discarded
        };

    }

}

#endif // !Y_Jive_Pattern_Dictionary_Included


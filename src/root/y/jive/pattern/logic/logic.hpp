//! \file


#ifndef Y_Jive_Logic_Included
#define Y_Jive_Logic_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Logic Pattern interface
        //
        //
        //______________________________________________________________________
        class Logic : public Pattern, public Patterns
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit Logic(const uint32_t) noexcept; //!< setu
            Logic(const Logic &); //!< duplicate

        public:
            virtual ~Logic() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t serialize(OutputStream &) const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void           load(InputStream &); //!< load save patterns

        private:
            Y_Disable_Assign(Logic); //!< discarded

        };

    }
    

}

#endif // !Y_Jive_Logic_Included


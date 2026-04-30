//! \file


#ifndef Y_Jive_Logic_Included
#define Y_Jive_Logic_Included 1

#include "y/jive/pattern.hpp"
#include "y/jive/pattern/within.hpp"

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
            explicit Logic(const uint32_t) noexcept; //!< setup
            Logic(const Logic &);                    //!< duplicate

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

            Logic & operator<<(Pattern * const);
            Logic & operator<<(const uint8_t);
            Logic & operator<<(const Within);

            static bool HaveSamePatterns(const Logic &lhs, const Logic &rhs) noexcept;


        private:
            Y_Disable_Assign(Logic); //!< discarded

        };

    }


}

#endif // !Y_Jive_Logic_Included


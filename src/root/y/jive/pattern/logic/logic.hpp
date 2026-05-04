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

            Logic & operator<<(Pattern * const); //!< append new patern \return *this
            Logic & operator<<(const uint8_t);   //!< append new single \return *this
            Logic & operator<<(const Within);    //!< append new range  \return *this

            //! \return true iff arguments have same patterns
            static bool    HaveSamePatterns(const Logic &, const Logic &) noexcept;
            OutputStream & emitLink(OutputStream &) const;

        protected:
            void optimizePatterns();
            void noMultiple() noexcept;
            void stripBasic(Patterns &basic) noexcept;

        private:
            Y_Disable_Assign(Logic); //!< discarded

        };

    }


}

#endif // !Y_Jive_Logic_Included


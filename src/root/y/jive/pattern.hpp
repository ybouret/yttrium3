//! \file

#ifndef Y_Jive_Pattern_Included
#define Y_Jive_Pattern_Included 1

#include "y/jive/source.hpp"
#include "y/type/fourcc.hpp"
#include "y/stream/serializable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Leading;

        //______________________________________________________________________
        //
        //
        //
        //! Pattern interface
        //
        //
        //______________________________________________________________________
        class Pattern : public Object, public Serializable
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit Pattern(const uint32_t)  noexcept; //!< setup
            explicit Pattern(const Pattern &) noexcept; //!< duplicate

        public:
            virtual ~Pattern() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool      takes(Token &, Source &) const  = 0; //!< \return true iff token is extracted from matching source
            virtual Pattern * clone()  const                  = 0; //!< \return clone
            virtual void      glean(Leading &) const noexcept = 0; //!< find leading bytes
            virtual bool      sound()          const noexcept = 0; //!< \return true iff takes doesn't return successful empty token
            bool              frail()          const noexcept;     //!< \return !sound()

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            size_t           emitUUID(OutputStream&) const; //!< emit UUID \return emitted bytes
            static Pattern * Load(InputStream &);           //!< \return reloaded pattern

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static bool      AreEqual(const Pattern &, const Pattern &) noexcept; //!<
            friend bool operator==(const Pattern &, const Pattern&) noexcept;
            friend bool operator!=(const Pattern &, const Pattern&) noexcept;
#endif
            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint32_t uuid;    //!< UUID
            const char     name[8]; //!< from UUID
            Pattern *      next;    //!< for list
            Pattern *      prev;    //!< for list

        private:
            Y_Disable_Assign(Pattern); //!< discarded
        };
    }
}

#endif // !Y_Jive_Pattern_Included


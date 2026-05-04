//! \file

#ifndef Y_Jive_Pattern_Included
#define Y_Jive_Pattern_Included 1

#include "y/jive/source.hpp"
#include "y/type/fourcc.hpp"
#include "y/stream/serializable.hpp"
#include "y/core/list/clone.hpp"
#include "y/object/counted.hpp"
#include "y/graphviz/vizible.hpp"

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
        class Pattern :
        public CountedObject,
        public Serializable,
        public Vizible
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
            virtual bool          takes(Token &, Source &) const  = 0; //!< \return true iff token is extracted from matching source
            virtual Pattern *     clone()  const                  = 0; //!< \return clone
            virtual void          glean(Leading &) const noexcept = 0; //!< find leading bytes
            virtual bool          sound()          const noexcept = 0; //!< \return true iff takes doesn't return successful empty token
            bool                  frail()          const noexcept;     //!< \return !sound()
            virtual bool          univocal()       const noexcept = 0; //!< \return true iff univocal result
            bool                  multiple()       const noexcept;     //!< \return !univocal()
            virtual OutputStream &viz(OutputStream &)       const = 0;
            virtual Pattern *     optimized()                     = 0;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            size_t           emitUUID(OutputStream&) const; //!< emit UUID \return emitted bytes
            static Pattern * Load(InputStream &);           //!< \return reloaded pattern
            bool             isBasic() const noexcept;

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static bool      AreEqual(const Pattern &, const Pattern &) noexcept; //!<
            friend bool operator==(const Pattern &, const Pattern&) noexcept;
            friend bool operator!=(const Pattern &, const Pattern&) noexcept;
#endif

            static Pattern * Among(const char * const, const size_t);
            static Pattern * Among(const char * const);
            static Pattern * Among(const String &);


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

        typedef ListOfCloneable<Pattern> Patterns; //!< alias
        typedef ArcPtr<const Pattern>    Motif;    //!< alias

    }
}

#endif // !Y_Jive_Pattern_Included



//! \file

#ifndef Y_Jive_Syntax_Compound_Included
#define Y_Jive_Syntax_Compound_Included 1

#include "y/jive/syntax/rule/internal.hpp"
#include "y/handy/basic/light/list.hpp"
#include "y/ability/freezable.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Parser;
        
        namespace Syntax
        {
            typedef Handy::BasicLightList<const Rule> RList; //!< alias
            typedef RList::NodeType                   RNode; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! Compound base class
            //
            //
            //__________________________________________________________________
            class Compound :
            public Internal,
            public Proxy<const RList>,
            public Freezable
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup empty
                /**
                 \param ruleName name
                 \param ruleUUID uuid
                 \param myParser optional parent parser
                 */
                template <typename ID>
                explicit Compound(const ID      & ruleName,
                                  const uint32_t  ruleUUID,
                                  Parser *  const myParser) :
                Internal(ruleName,ruleUUID),
                rlist(),
                parser(myParser)
                {
                }

                //! cleanup
                virtual ~Compound() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream & vizLink(OutputStream &) const;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                Compound & operator<<(const Rule &);       //!< append a rule \return *this
                Compound & operator<<(const char);         //!< append a mark \return *this
                Compound & operator<<(const String     &); //!< append an eponymous term \return *this
                Compound & operator<<(const char * const); //!< append an eponymous term \return *this

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________

            private:
                Y_Disable_Copy_And_Assign(Compound); //!< discarded
                Y_Proxy_Decl();
            protected:
                RList rlist;

            public:
                Parser * const parser; //!< optional parent parser
            };

        }

    }

}

#endif // !Y_Jive_Syntax_Compound_Included

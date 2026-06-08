
//! \file

#ifndef Y_Jive_Syntax_Aggregate_Included
#define Y_Jive_Syntax_Aggregate_Included 1

#include "y/jive/syntax/rule/compound.hpp"
#include "y/type/fourcc.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            //__________________________________________________________________
            //
            //
            //! Aggregate duty
            //
            //__________________________________________________________________
            enum Duty
            {
                Entitled, //!< never yields
                Grouping, //!< always yields
                Yielding  //!< only if 1 node
            };

            //__________________________________________________________________
            //
            //
            //
            //! Aggregate of rules
            //
            //
            //__________________________________________________________________
            class Aggregate : public Compound
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('A','G','G','_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup emtpy \param ruleName name \param ruleDuty duty
                template <typename ID> inline
                explicit Aggregate(const ID &     ruleName,
                                   const Duty     ruleDuty,
                                   Parser * const myParser) :
                Compound(ruleName,UUID,myParser),
                duty(ruleDuty)
                {

                }

                //! cleanup
                virtual ~Aggregate() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual const char *   vizShape()     const noexcept;
                virtual const char *   vizStyle()     const noexcept;
                Y_Jive_Syntax_Rule_Decl(); //!< accepts

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Duty           duty; //!< duty
            private:
                Y_Disable_Copy_And_Assign(Aggregate); //!< discarded
            };

        }

    }
}

#endif // !Y_Jive_Syntax_Aggregate_Included


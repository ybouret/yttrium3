#include "y/chemical/formula.hpp"

#if !defined(NDEBUG)
#include "y/jive/syntax/rule.hpp"
#endif

namespace Yttrium
{
    namespace Chemical
    {

        Formula_:: Formula_(XNode * const xnode) noexcept :
        CountedObject(),
        code(xnode)
        {
            assert(code);
        }

        Formula_:: ~Formula_() noexcept
        {
            assert(code);
            Destroy(code);
        }

        Formula_ * Formula_:: Create(XNode * const xnode)
        {
            assert(xnode);
            assert(Formula::CallSign == *xnode->rule.name);
            try
            {

                return new Formula_(xnode);
            }
            catch(...)
            {
                delete xnode;
                throw;
            }
        }

        const char * const Formula::CallSign = "Formula";

        Formula:: Formula(XNode * const xnode) :
        ArcPtr<Formula_>( Formula_::Create(xnode) )
        {
        }

        Formula:: ~Formula() noexcept
        {
        }

        Formula:: Formula(const Formula &f) noexcept :
        ArcPtr<Formula_>(f)
        {
        }

    }

}

#include "y/chemical/weasel.hpp"
#include "y/chemical/formula/translator.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        String Formula:: makeName(int * const pz) const
        {
            static Formula::Translator &ft = Weasel::Instance().formulaTranslator;
            return ft.makeName(*this,pz);
        }

        String  Formula:: makeHTML() const
        {
            static Formula::Translator &ft = Weasel::Instance().formulaTranslator;
            return ft.makeHTML(*this);
        }

    }

}

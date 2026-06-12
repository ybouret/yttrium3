
#include "y/chemical/formula/translator.hpp"
#include "y/string/format.hpp"
#include "y/ascii/convert.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Formula::Translator:: ~Translator() noexcept
        {
        }

        Formula:: Translator:: Translator(const Identifier &id) :
        Jive::Editor(id),
        output(FormulaToName),
        frag(),
        coef(),
        sgnv(),
        z(0)
        {
            Y_Jive_OnTerminal(Translator,FRAG);
            Y_Jive_OnTerminal(Translator,COEF);

            on('+', this, & Translator::onPLUS);
            on('-', this, & Translator::onMINUS);


            Y_Jive_OnInternal(Translator,Formula);
            Y_Jive_OnInternal(Translator,GRP);
            Y_Jive_OnInternal(Translator,STO);
            Y_Jive_OnInternal(Translator,Z);

        }

        void Formula::Translator:: initialize() noexcept
        {
            frag.free();
            coef.free();
            sgnv.free();
            z = 0;
        }

        void Formula::Translator:: onFRAG(const Lexeme &lexeme)
        {
            frag << lexeme.str();
            std::cerr << "frag=" << frag << std::endl;
        }

        void Formula::Translator:: onCOEF(const Lexeme &lexeme)
        {
            coef << lexeme.str();
            std::cerr << "coef=" << coef << std::endl;
        }

        void Formula::Translator:: onPLUS(const Lexeme &)
        {
            sgnv << '+';
        }

        void Formula::Translator:: onMINUS(const Lexeme &)
        {
            sgnv << '-';
        }




        void Formula::Translator:: onFormula(const size_t) noexcept
        {
            assert(frag.size()>0);
            std::cerr << "Formula='" << frag.tail() << "'/z=" << z << std::endl;
        }

        void Formula::Translator:: onGRP(const size_t n)
        {
            std::cerr << "grouping/" << n << " @depth=" << depth << std::endl;
            assert(n>=1);
            assert(frag.size()>=n);
            const size_t nfrag = frag.size();
            const bool   paren = (depth>1);
            String       group; if(paren) group << '(';
            for(size_t i=nfrag-(n-1);i<=nfrag;++i)
            {
                group += frag[i];
            }
            if(paren) group << ')';
            for(size_t i=n;i>0;--i) frag.popTail();
            frag << group;
            std::cerr << frag << std::endl;
        }



        void Formula::Translator:: onSTO(const size_t
#if !defined(NDEBUG)
                                         n
#endif
        )
        {
            assert(2==n);
            assert(frag.size()>0);
            assert(coef.size()>0);
            const String &cf = coef.tail();
            switch(output)
            {
                case FormulaToName: frag.tail() +=           cf;            break;
                case FormulaToMath: frag.tail() += "_{"    + cf + "}";      break;
                case FormulaToHTML: frag.tail() += "<sub>" + cf + "</sub>"; break;
            }
            coef.popTail();
        }

        void Formula::Translator:: onZ(const size_t n)
        {
            assert(n==1||n==2);
            assert(sgnv.size()>0);

            const char c = sgnv.tail();
            switch(c)
            {
                case '+' : z=1;  break;
                case '-' : z=-1; break;
            }
            sgnv.popTail();

            String zstr;
            if(n>1)
            {
                static const char * const varPart = "charge coefficient";
                assert(coef.size()>0);
                const String &s  = coef.tail();
                const int     cf = ASCII::Convert::To<int>(s,CallSign,varPart);
                if(cf<=0) throw Specific::Exception(CallSign, "%s cannot be zero", varPart);

                if(cf>1)
                {
                    z   *= cf;
                    zstr = s;
                }
                coef.popTail();
            }

            zstr += c;
            std::cerr << "zstr=" << zstr << std::endl;

            assert(frag.size()>0);

            switch(output)
            {
                case FormulaToName: frag.tail() += '^'     + zstr;            break;
                case FormulaToMath: frag.tail() += "^{"    + zstr + "}";      break;
                case FormulaToHTML: frag.tail() += "<sup>" + zstr + "</sup>"; break;
            }
        }

        String Formula:: Translator:: makeName(const Formula &formula, int  * const pz)
        {
            Jive::Editor &self = *this;
            output = FormulaToName;
            self(formula->code);
            if(pz) *pz = z;
            String name = frag.tail();
            initialize();
            return name;
        }

        String Formula:: Translator::makeHTML(const Formula &formula)
        {
            Jive::Editor &self = *this;
            output = FormulaToHTML;
            self(formula->code);
            String html = frag.tail();
            initialize();
            return html;
        }



    }
}

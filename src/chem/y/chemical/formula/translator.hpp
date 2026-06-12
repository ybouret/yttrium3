
//! \file

#ifndef Y_Chemical_Formula_Translator_Included
#define Y_Chemical_Formula_Translator_Included 1

#include "y/chemical/formula.hpp"
#include "y/jive/editor.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        enum FormulaOutput
        {
            FormulaToName,
            FormulaToMath,
            FormulaToHTML
        };

        class Formula:: Translator : public Jive::Editor
        {
        public:
            explicit Translator(const Identifier &);
            virtual ~Translator() noexcept;

            virtual void initialize() noexcept;

            FormulaOutput output;

        private:
            Y_Disable_Copy_And_Assign(Translator);
            Vector<String> frag;
            Vector<String> coef;
            Vector<char>   sgnv;
            int            z;

            void onFRAG(const Lexeme &);
            void onCOEF(const Lexeme &);
            void onPLUS(const Lexeme &);
            void onMINUS(const Lexeme &);
            void onFormula(const size_t) noexcept;
            void onGRP(const size_t);
            void onSTO(const size_t);
            void onZ(const size_t);
            
        };
    }
}

#endif // !Y_Chemical_Formula_Translator_Included

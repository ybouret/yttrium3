
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

        //______________________________________________________________________
        //
        //
        //
        //! Select output for formula translator
        //
        //
        //______________________________________________________________________
        enum FormulaOutput
        {
            FormulaToName, //!< build name
            FormulaToMath, //!< build LaTeX math
            FormulaToHTML  //!< build html label
        };

        //______________________________________________________________________
        //
        //
        //
        //! Formula translator
        //
        //
        //______________________________________________________________________
        class Formula:: Translator : public Jive::Editor
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Translator(const Identifier &); //!< setup
            virtual ~Translator() noexcept;          //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void initialize() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String        makeName(const Formula &, int * const = 0); //!< \return name with optional charge storage
            String        makeHTML(const Formula &);                  //!< \return HTML label

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            FormulaOutput output; //!< output to produce

        private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
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
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            
        };
    }
}

#endif // !Y_Chemical_Formula_Translator_Included

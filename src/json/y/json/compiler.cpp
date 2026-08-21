
#include "y/json/compiler.hpp"
#include "y/jive/parser.hpp"
#include "y/check/static.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"
#include "y/jive/editor.hpp"
#include "y/ascii/convert.hpp"

namespace Yttrium
{
    namespace JSON
    {

        const char * const Compiler:: CallSign = "JSON";

        namespace
        {
            static const char NumberRX[] =
            "[-+]?[:digit:]+";

        }


        class Compiler:: Code :
        public Jive::Parser,
        public Jive::Editor
        {
        public:
            typedef Jive::Syntax::Grammar::XNode XNode; // gcc bug ?

            explicit Code();
            virtual ~Code() noexcept;

            void compile(Value &, Jive::Module * const);



        private:
            Y_Disable_Copy_And_Assign(Code);
            Array              vstk;
            Vector<SharedPair> pstk;

            void setupParser();
            void setupEditor();
            inline virtual void initialize()
            {
                vstk.free();
                pstk.free();
            }

            inline virtual void printState() const
            {
                std::cerr << "(*) vstk=" << vstk;
                if(pstk.size()>0) std::cerr << " | pstk=" << pstk;
                std::cerr << std::endl;
            }

            //------------------------------------------------------------------
            //
            // TERMINAL
            //
            //------------------------------------------------------------------
            inline void onNUMBER(const Lexeme &lexeme)
            {
                const String s = lexeme.str();
                const Number x = ASCII::Convert::To<Number>(s,"Number",0);
                Value  v(x);
                vstk.add(v);
            }

            inline void onfalse(const Lexeme &) {
                Value v(false); vstk.add(v);
            }

            inline void ontrue(const Lexeme &) {
                Value v(true); vstk.add(v);
            }

            inline void onnull(const Lexeme&) {
                Value v; vstk.add(v);
            }

            inline void onSTRING(const Lexeme &lexeme) {
                const String s = lexeme.str(); //std::cerr << "s='" << s << "'" << std::endl;
                Value v(s);
                vstk.add(v);
            }


            //------------------------------------------------------------------
            //
            // INTERNAL
            //
            //------------------------------------------------------------------
            inline void onEMPTY_ARRAY(const size_t)
            {
                Value v(AsArray);
                vstk.add(v);
            }

            inline void onHEAVY_ARRAY(const size_t n)
            {
                assert(n>0);
                assert(vstk.size()>=n);
                Value        val(AsArray);
                {
                    Array &      arr = val.as<Array>();
                    for(size_t i=vstk.size()-(n-1),j=n;j>0;--j,++i)
                    {
                        arr.add(vstk[i]);
                    }
                }
                for(size_t j=n;j>0;--j) vstk.popTail();
                vstk.add(val);
            }

            inline void onEMPTY_OBJECT(const size_t)
            {
                Value v(AsObject);
                vstk.add(v);
            }

            inline void onPAIR(const size_t)
            {
                assert(vstk.size()>=2);
                Value v; v.xch(vstk.tail()); vstk.popTail();
                Value s; s.xch(vstk.tail()); vstk.popTail(); assert(IsString == s.type);
                SharedPair P = new Pair( s.as<String>() );
                P->v.xch(v);
                pstk << P;
            }

            inline void onHEAVY_OBJECT(const size_t n)
            {
                assert(n>0);
                assert(n<=pstk.size());
                Value val(AsObject);
                {
                    JSON::Object &obj = val.as<JSON::Object>();
                    for(size_t i=pstk.size()-(n-1),j=n;j>0;--j,++i)
                    {
                        const SharedPair &P = pstk[i];
                        if(!obj.insert(P))
                        {
                            throw Specific::Exception(CallSign,"multiple Pair.key='%s'", P->k.c_str());
                        }
                    }
                    for(size_t j=n;j>0;--j) pstk.popTail();

                }
                vstk.add(val);
            }


        };

        Compiler:: Code:: ~Code() noexcept {}

        Compiler:: Code:: Code() :
        Jive::Parser(CallSign),
        Jive::Editor(name),
        vstk(),
        pstk()
        {
            Y_STATIC_CHECK( Y_Is_SuperSubClass_Strict(Object,Code), BadCode);
            setupParser();
            setupEditor();
        }

        void Compiler:: Code:: setupParser()
        {
            //------------------------------------------------------------------
            //
            //
            // top level
            //
            //
            //------------------------------------------------------------------
            Alternate  &JSON   = alt("JSON");
            Alternate  &VALUE  = alt("VALUE");
            const Rule &STRING = use( TypeToType<Jive::Lexical::JString>(), "STRING");

            //------------------------------------------------------------------
            //
            //
            // Arrays
            //
            //
            //------------------------------------------------------------------
            {
                const Rule &EMPTY_ARRAY = (agg("EMPTY_ARRAY") << '[' << ']');
                const Rule &HEAVY_ARRAY = (agg("HEAVY_ARRAY") << '[' << VALUE << extra(',',VALUE) << ']');
                const Rule &ARRAY       = (alt("ARRAY") << EMPTY_ARRAY << HEAVY_ARRAY);
                VALUE << ARRAY;
                JSON  << ARRAY;
            }

            //------------------------------------------------------------------
            //
            //
            // Objects
            //
            //
            //------------------------------------------------------------------
            {
                const Rule &PAIR         = (agg("PAIR") << STRING << ':' << VALUE);
                const Rule &EMPTY_OBJECT = (agg("EMPTY_OBJECT") << '{' << '}');
                const Rule &HEAVY_OBJECT = (agg("HEAVY_OBJECT") << '{' << PAIR << extra(',',PAIR) << '}');
                const Rule &OBJECT       = (alt("OBJECT") << EMPTY_OBJECT << HEAVY_OBJECT);
                VALUE << OBJECT;
                JSON  << OBJECT;
            }

            //------------------------------------------------------------------
            //
            //
            // gather value
            //
            //
            //------------------------------------------------------------------
            VALUE << STRING << term("NUMBER",NumberRX) << "true" << "false" << "null";

            //------------------------------------------------------------------
            //
            //
            // lexical only rules
            //
            //
            //------------------------------------------------------------------
            drop("blank", "[:blank:]");
            endl("endl",  "[:endl:]");

            //------------------------------------------------------------------
            //
            //
            // Validate
            //
            //
            //------------------------------------------------------------------
            validate();
        }




        void Compiler:: Code:: setupEditor()
        {
            Y_Jive_OnTerminal(Code,NUMBER);
            Y_Jive_OnTerminal(Code,false);
            Y_Jive_OnTerminal(Code,true);
            Y_Jive_OnTerminal(Code,null);
            Y_Jive_OnTerminal(Code,STRING);

            Y_Jive_OnInternal(Code,EMPTY_ARRAY);
            Y_Jive_OnInternal(Code,HEAVY_ARRAY);
            Y_Jive_OnInternal(Code,EMPTY_OBJECT);
            Y_Jive_OnInternal(Code,HEAVY_OBJECT);
            Y_Jive_OnInternal(Code,PAIR);


        }


        void Compiler:: Code:: compile(Value &v, Jive::Module *const m)
        {
            Jive::Editor & edit = *this;
            AutoPtr<XNode> ast  = getAST(m); assert(ast.isValid());
            edit(ast,Jive::Rigorous);
            assert(1==vstk.size());
            assert(0==pstk.size());
            v.xch(vstk.head()); vstk.free();
            assert(IsObject==v.type||IsArray==v.type);
        }

        ////////////////////////////////////////////////////////////////////////

        Compiler:: Compiler() :
        code( new Code() ),
        verbose(code->verbose)
        {
        }


        Compiler:: ~Compiler() noexcept
        {
            Destroy(code);
        }

        void Compiler:: render() const
        {
            assert(code);
            code->render();
        }

        void Compiler:: operator()(Value &v, Jive::Module * const m)
        {
            assert(0!=m);
            v.nullify();
            code->compile(v,m);

        }


    }
}

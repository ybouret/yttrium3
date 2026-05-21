//! \file

#ifndef Y_Jive_Multi_Lines_Comment_Included
#define Y_Jive_Multi_Lines_Comment_Included 1

#include "y/jive/lexical/plugin.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            //__________________________________________________________________
            //
            //
            //
            //! Multi Lines Comment Plugin
            //
            //
            //__________________________________________________________________
            class MultiLinesComment : public Plugin
            {
            public:
                //! setup
                /**
                 \param id  name
                 \param ini trigger regular expression
                 \param end trigger return from the plugin
                 \param lxr parent lexer
                 */
                template <typename ID, typename INI, typename END>
                explicit MultiLinesComment(const ID  & id,
                                           const INI & ini,
                                           const END & end) :
                Plugin(id,ini,RejectEOS)
                {
                    (void) back(end);
                    setup();
                }

                //! cleanup
                virtual ~MultiLinesComment() noexcept;

            private:
                Y_Disable_Copy_And_Assign(MultiLinesComment); //!< discaded
                void setup(); //!< drop dot, forward endl


            };

#define Y_Jive_Multi_Lines_Comment(CLASS,INI,END)    \
/**/    class CLASS : public MultiLinesComment    \
/**/    {                                         \
/**/    public:                                   \
/**/        template <typename ID>                \
/**/        inline explicit CLASS(const ID &id):  \
/**/        MultiLinesComment(id,INI,END)    {}   \
/**/        inline virtual ~CLASS() noexcept {}   \
/**/    private:                                  \
/**/        Y_Disable_Copy_And_Assign(CLASS);     \
/**/    }


            Y_Jive_Multi_Lines_Comment(C_Comment,"/\\*","\\*/");

        }

    }

}

#endif // !Y_Jive_Multi_Lines_Comment_Included


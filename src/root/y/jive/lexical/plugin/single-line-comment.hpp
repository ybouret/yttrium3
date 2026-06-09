
//! \file

#ifndef Y_Jive_Single_Line_Comment_Included
#define Y_Jive_Single_Line_Comment_Included 1

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
            //! Single Line Comment Plugin
            //
            //
            //__________________________________________________________________
            class SingleLineComment : public Plugin
            {
            public:
                //! setup
                /**
                 \param id  name
                 \param rx  trigger regular expression
                 */
                template <typename ID, typename RX>
                explicit SingleLineComment(const ID & id,
                                           const RX & rx) :
                Plugin(id,rx,AcceptEOS)
                {
                    setup();
                }
                
                virtual ~SingleLineComment() noexcept; //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(SingleLineComment); //!< discarded
                void setup(); //!< drop dot, back on endl
            };

            //! helper
#define Y_Jive_Single_Line_Comment(CLASS,EXPR)    \
/**/    class CLASS : public SingleLineComment    \
/**/    {                                         \
/**/    public:                                   \
/**/        template <typename ID>                \
/**/        inline explicit CLASS(const ID &id):  \
/**/        SingleLineComment(id,EXPR)       {}   \
/**/        inline virtual ~CLASS() noexcept {}   \
/**/    private:                                  \
/**/        Y_Disable_Copy_And_Assign(CLASS);     \
/**/    }


            Y_Jive_Single_Line_Comment(ShellComment,'#'); //!< shell comment
            
        }

    }

}

#endif // !Y_Jive_Single_Line_Comment_Included


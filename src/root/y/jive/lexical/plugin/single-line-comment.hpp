
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
                 \param lxr parent lexer
                 */
                template <typename ID, typename RX>
                explicit SingleLineComment(const ID & id,
                                           const RX & rx,
                                           Lexer    & lxr) :
                Plugin(id,rx,lxr)
                {
                    setup();
                }
                
                virtual ~SingleLineComment() noexcept; //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(SingleLineComment); //!< discarded
                void setup(); //!< drop dot, back on endl
            };


            class HashTagComment : public SingleLineComment
            {
            public:
                template <typename ID>
                inline explicit HashTagComment(const ID &id, Lexer &lxr) :
                SingleLineComment(id,'#',lxr)
                {
                }
                
                inline virtual ~HashTagComment() noexcept {}

            private:
                Y_Disable_Copy_And_Assign(HashTagComment);
            };


        }

    }

}

#endif // !Y_Jive_Single_Line_Comment_Included


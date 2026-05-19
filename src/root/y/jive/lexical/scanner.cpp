
#include "y/jive/lexical/scanner.hpp"
#include "y/handy/basic/light/list.hpp"
#include "y/threading/single-threaded-class.hpp"
namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            typedef Handy::BasicLightList<const Rule,SingleThreadedClass> RuleList;

            class Scanner:: Code : public Object
            {
            public:
                inline explicit Code(const Identifier &sid) : name(sid)
                {
                }


                inline virtual ~Code() noexcept
                {
                }

                const Identifier name;

            private:
                Y_Disable_Copy_And_Assign(Code);
            };

            Scanner::Code * Scanner:: CreateCode(const Identifier &sid)
            {
                return new Code(sid);
            }


            Scanner:: ~Scanner() noexcept
            {

            }
            
        }

    }

}


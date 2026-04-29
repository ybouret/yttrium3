
//! file

#ifndef Y_Identifier_Included
#define Y_Identifier_Included


#include "y/string.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{

    class Identifier : public ArcPtr<const String>
    {
    public:
        typedef ArcPtr<const String> SharedString;

        Identifier(const String * const) noexcept;
        Identifier(const Identifier &)   noexcept;
        Identifier(const String &);
        Identifier(const char * const);
        Identifier(const char);


        virtual ~Identifier() noexcept;

    private:
        Y_Disable_Assign(Identifier);
    };

}

#endif // !Y_Identifier_Included


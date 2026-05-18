
//! file

#ifndef Y_Identifiers_Included
#define Y_Identifiers_Included


#include "y/stream/identifier.hpp"
#include "y/container/associative/hash/set.hpp"

namespace Yttrium
{

    typedef HashSet<String,Identifier> IdentifierDB;

    class Identifiers : public IdentifierDB
    {
    public:
        explicit Identifiers();
        virtual ~Identifiers() noexcept;
        
    private:
        Y_Disable_Copy_And_Assign(Identifiers);
    };


}

#endif // !Y_Identifiers_Included

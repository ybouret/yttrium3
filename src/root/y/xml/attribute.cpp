
#include "y/xml/attribute.hpp"

namespace Yttrium
{
    namespace XML
    {
        Attribute:: ~Attribute() noexcept
        {
        }

        std::ostream & operator<<(std::ostream &os, const Attribute &self)
        {
            assert(self.name);
            assert(self.args);
            assert(self.show);
            
            return self.show(os << ' ' << self.name << '=',self.args);
        }

        Attribute:: Attribute(const Attribute &_) noexcept :
        name(_.name),
        args(_.args),
        show(_.show)
        {

        }


    }

}


#include "y/ability/logging.hpp"
#include "y/xml/log.hpp"

namespace Yttrium
{
    Logging::  Logging() noexcept { }
    Logging:: ~Logging() noexcept { }

    std::ostream & Logging:: writeXML(std::ostream &os) const
    {
        bool verbose = true;
        XML::Log xml(os,verbose);
        toXML(xml);
        return os;
    }



}


#include "y/chemical/plexus/conservation/law/broken.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

            Broken:: Broken(const Law &_law, const xreal_t _bad, XWritable & _prj) noexcept :
            law(_law),
            bad(_bad),
            prj(_prj)
            {

            }

            Broken:: Broken(const Broken &_) noexcept :
            law(_.law),
            bad(_.bad),
            prj(_.prj)
            {

            }
            Broken:: ~Broken() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Broken &self)
            {
                os << self.bad.str() << " @" << self.law;
                return os;
            }

        }

    }

}



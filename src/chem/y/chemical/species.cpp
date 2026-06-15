

#include "y/chemical/species.hpp"
#include "y/stream/output.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        Species:: ~Species() noexcept
        {
        }

        Species:: Species(const Formula &f, const size_t i) :
        CountedObject(),
        Formula(f),
        Indexed(i),
        z(0)
        {
            String _ = makeName(& Coerce(z) );
            Coerce(name).xch(_);
        }

        OutputStream & Species:: viz(OutputStream &fp,
                                     const char * const color,
                                     const char * const style) const
        {
            nodeName(fp) << '[';
            fp << "label=<" << makeHTML() << ">,shape=box";
            if(color) fp << ",color=" << color << ",fontcolor=" << color;
            if(style) fp << ",style=\"" << style << "\"";
            return Endl(fp << ']');
        }
    }

}



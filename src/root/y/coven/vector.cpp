
#include "y/coven/vector.hpp"

namespace Yttrium
{

    namespace Coven
    {

        Vector:: ~Vector() noexcept
        {
        }

        Vector:: Vector(const Metrics &metrics) :
        Object(), Metrics(metrics), IVector(dimensions),
        ncof(0),
        mod2(0),
        next(0),
        prev(0)
        {

        }

        Vector:: Vector(const Vector &v) :
        Container(),
        Object(),
        Metrics(v),
        IVector(CopyOf,v),
        ncof(v.ncof),
        mod2(v.mod2),
        next(0),
        prev(0)
        {
        }



    }

}

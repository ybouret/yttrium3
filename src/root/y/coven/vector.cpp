
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

        void Vector:: ldz() noexcept
        {
            Coerce(ncof) = 0;
            Coerce(mod2).ldz();
            IVector &self = *this;
            for(size_t i=self.size();i>0;--i) self[i].ldz();
        }

        void Vector:: update()
        {
            const IVector &self = *this;
            try
            {
                Coerce(ncof) = 0;
                apn & n2 = Coerce(mod2);
                n2.ldz();
                for(size_t i=dimensions;i>0;--i)
                {
                    const apz &z = self[i];
                    switch(z.s)
                    {
                        case __Zero__: continue;
                        case Positive:
                        case Negative:
                            ++Coerce(ncof);
                            n2 += z.n.mod2();
                            continue;
                    }
                }
            }
            catch(...)
            {
                ldz();
                throw;
            }
        }


    }

}

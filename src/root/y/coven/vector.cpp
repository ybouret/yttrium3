
#include "y/coven/vector.hpp"

namespace Yttrium
{
    namespace Coven
    {
        Vector:: ~Vector() noexcept
        {
        }

        Vector:: Vector(const Metrics &metrics) :
        Object(), Metrics(metrics), zVector(dimensions),
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
        zVector(CopyOf,v),
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
            zVector &self = *this;
            for(size_t i=self.size();i>0;--i) self[i].ldz();
        }

        void Vector:: update()
        {
            const zVector &self = *this;
            try
            {
                Coerce(ncof) = 0;
                apn &  nrm2  = Coerce(mod2);
                nrm2.ldz();
                for(size_t i=dimensions;i>0;--i)
                {
                    const apz &z = self[i];
                    switch(z.s)
                    {
                        case __Zero__: continue;
                        case Positive:
                        case Negative:
                            ++Coerce(ncof);
                            nrm2 += z.n.mod2();
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

#include "y/coven/univocal.hpp"

namespace Yttrium
{
    namespace Coven
    {
        bool Vector:: univocal()
        {
            if( Univocal::Make(*this) )
            {
                update();
                return true;
            }
            else
            {
                ldz();
                return false;
            }
        }

    }

}

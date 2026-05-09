
#include "y/coven/vector.hpp"

namespace Yttrium
{
    namespace Coven
    {
        Vector:: ~Vector() noexcept
        {
        }

        Vector:: Vector(const Metrics &metrics) :
        Object(), Metrics(metrics), zVector(dimension),
        ncof(0),
        nnul(0),
        npos(0),
        nneg(0),
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
        nnul(v.nnul),
        npos(v.npos),
        nneg(v.nneg),
        mod2(v.mod2),
        next(0),
        prev(0)
        {
        }

        Vector & Vector:: operator=( const Vector &source )
        {
            try
            {
                Coerce(ncof) = source.ncof;
                Coerce(nnul) = source.nnul;
                Coerce(npos) = source.npos;
                Coerce(nneg) = source.nneg;
                Coerce(mod2) = source.mod2;
                for(size_t i=dimension;i>0;--i)
                    (*this)[i] = source[i];
            }
            catch(...)
            {
                ldz();
                throw;
            }
            return *this;
        }

        void Vector:: ldz() noexcept
        {
            Coerce(ncof) = 0;
            Coerce(nnul) = 0;
            Coerce(npos) = 0;
            Coerce(nneg) = 0;
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
                for(size_t i=dimension;i>0;--i)
                {
                    const apz &z = self[i];
                    switch(z.s)
                    {
                        case __Zero__: ++Coerce(nnul); continue;
                        case Positive: ++Coerce(npos); nrm2 += z.n.mod2(); continue;
                        case Negative: ++Coerce(nneg); nrm2 += z.n.mod2(); continue;
                    }
                }
                Coerce(ncof) = Coerce(npos) + Coerce(nneg);
            }
            catch(...)
            {
                ldz();
                throw;
            }
        }

        SignType Vector:: Compare(const Vector &lhs, const Vector &rhs) noexcept
        {
            assert(lhs.size()==rhs.size());

            // using ncof
            switch( Sign::Of(lhs.ncof,rhs.ncof) )
            {
                case Negative: return Negative;
                case Positive: return Positive;
                case __Zero__: break;
            }

            // using mod2
            switch( apn::Cmp(lhs.mod2,rhs.mod2) )
            {
                case Negative: return Negative;
                case Positive: return Positive;
                case __Zero__: break;
            }

            // using lexicographic
            {
                const size_t n = lhs.size();
                for(size_t i=1;i<=n;++i)
                {
                    switch( apz::Cmp(lhs[i],rhs[i]))
                    {
                        case Negative: return Negative;
                        case Positive: return Positive;
                        case __Zero__: continue;
                    }
                }
            }

            return __Zero__;
        }

        SignType Vector:: Cmp(const Vector * const lhs, const Vector * const rhs) noexcept
        {
            assert(lhs); assert(rhs); return Compare(*lhs,*rhs);
        }

        bool operator==(const Vector &lhs, const Vector &rhs) noexcept
        {
            return __Zero__ == Vector::Compare(lhs,rhs);
        }

        bool operator!=(const Vector &lhs, const Vector &rhs) noexcept
        {
            return __Zero__ != Vector::Compare(lhs,rhs);
        }


        std::ostream & operator<<(std::ostream &os, const Vector &v)
        {
            { const zVector &zv = v; os << zv; }
            return os << " # |#" << v.ncof << "|^2=" << v.mod2;
        }

        void Vector:: exchange(Vector &v) noexcept
        {
            xch(v);
            CoerceSwap(ncof,v.ncof);
            Coerce(mod2).xch( Coerce(v.mod2) );
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

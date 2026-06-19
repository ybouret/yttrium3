
#include "y/chemical/reactive/components.hpp"
#include "y/exception.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Components:: ~Components() noexcept
        {
        }

        Components:: Components(const String &eqName, const size_t eqIndx) :
        Indexed(eqName,eqIndx),
        kind(Outlawed),
        size(0),
        reac(AsSpec),
        prod(AsSpec),
        one(1)
        {

        }

        EqKind Components:: computeKind() const noexcept
        {
            if(reac->size)
            {
                if(prod->size)
                {
                    assert(size==prod->size+reac->size);
                    return BothWays;
                }
                else
                {
                    assert(size==reac->size);
                    return ReacOnly;
                }
            }
            else
            {
                if(prod->size)
                {
                    assert(size==prod->size);
                    return ProdOnly;
                }
                else
                {
                    assert(0==size);
                    return Outlawed;
                }
            }

        }

        void Components:: checkUnused(const char *const fn, const Species &sp) const
        {
            const char * const id   = sp.name.c_str();
            if(reac.hired(sp)) throw Specific::Exception(fn,"'%s' already in reactants",id);
            if(prod.hired(sp)) throw Specific::Exception(fn,"'%s' already in products",id);
        }

        void Components:: addReac(const unsigned nu, const Species &sp)
        {
            static const char  fn[] = "Components::addReac";
            if(frozen) throw Specific::Exception(fn,"frozen for '%s'", sp.name.c_str());
            checkUnused(fn,sp);
            Coerce(reac).hire(nu,sp);
            ++Coerce(size);
            Coerce(kind) = computeKind();
        }

        void Components:: addProd(const unsigned nu, const Species &sp)
        {
            static const char  fn[] = "Components::addProd";
            if(frozen) throw Specific::Exception(fn,"frozen for '%s'", sp.name.c_str());
            checkUnused(fn,sp);
            Coerce(prod).hire(nu,sp);
            ++Coerce(size);
            Coerce(kind) = computeKind();

        }

        bool Components:: electroneutral() const
        {
            return reac.charge() == prod.charge();
        }

        bool  Components:: atLeastOneItem() const
        {
            if(Outlawed!=kind)
            {
                assert(reac->size>0 || prod->size>0);
                return true;
            }
            else
            {
                return false;
            }
        }

        xreal_t Components:: massAction(const xreal_t     K,
                                        XMul &            X,
                                        const XReadable & C,
                                        const Level       L) const
        {
            X.set(K); reac.massAction(X,C,L);
            const xreal_t lhs = X();

            X.set(one); prod.massAction(X,C,L);
            const xreal_t rhs = X();

            return lhs-rhs;
        }

        xreal_t Components:: massAction(const xreal_t K, XMul &X, const XReadable &C, const Level L, const xreal_t xi) const
        {
            X.set(K); reac.massAction(X,C,L,-xi);
            const xreal_t lhs = X();

            X.set(one); prod.massAction(X,C,L,xi);
            const xreal_t rhs = X();

            return lhs-rhs;
        }

        void Components::  saveMove(XWritable &C, const Level L, const xreal_t xi) const noexcept
        {
            reac.safeMove(C,L,-xi);
            prod.safeMove(C,L,xi);
        }

        xreal_t Components:: extent(const XReadable &Cold, const XReadable &Cnew, const Level L, XAdd &xadd) const
        {
            xadd.ldz();
            for(const Actor *ac=prod->head;ac;ac=ac->next)
            {
                const size_t  i  = ac->sp.indx[L];
                const xreal_t xi = (Cnew[i]-Cold[i])/ac->xn;
                xadd += xi;
            }

            for(const Actor *ac=reac->head;ac;ac=ac->next)
            {
                const size_t  i  = ac->sp.indx[L];
                const xreal_t xi = (Cold[i]-Cnew[i])/ac->xn;
                xadd += xi;
            }

            const xreal_t den = (real_t) size;

            return xadd()/den;
        }


        bool Components:: hired(const Species &sp) const noexcept
        {
            return reac.hired(sp) || prod.hired(sp);
        }


        bool Components:: linkedTo(const Components &other) const noexcept
        {
            for(const Actor *ac=reac->head;ac;ac=ac->next)
                if(other.hired(ac->sp)) return true;

            for(const Actor *ac=prod->head;ac;ac=ac->next)
                if(other.hired(ac->sp)) return true;

            return false;

        }

        OutputStream & Components:: vizSelf(OutputStream &fp,
                                            const char * const color,
                                            const char * const style) const
        {
            nodeName(fp) << '[';
            Label(fp,name);
            fp << ",shape=cylinder";
            if(color) fp << ",color=" << color << ",fontcolor=" << color;
            if(style) fp << ",style=\"" << style << "\"";
            return Endl(fp << ']');
        }


        static inline void arrowLegend(OutputStream &     fp,
                                       const unsigned     nu,
                                       const char * const color)
        {
            fp << "arrowhead=normal";
            if(nu>1)
            {
                fp(",label=\"%u\"",nu);
            }
            if(color) fp << ",color=\"" << color << "\",fontcolor=\"" << color << "\"";
        }

        OutputStream & Components:: vizLink(OutputStream &fp,
                                            const char * const color) const
        {
            for(const Actor *ac=reac->head;ac;ac=ac->next)
            {
                ac->sp.to(this,fp) << '[';
                arrowLegend(fp,ac->nu,color);
                Endl(fp<<']');
            }

            for(const Actor *ac=prod->head;ac;ac=ac->next)
            {
                to(& ac->sp,fp) << '[';
                arrowLegend(fp,ac->nu,color);
                Endl(fp<<']');
            }
            
            return fp;
        }


    }

}



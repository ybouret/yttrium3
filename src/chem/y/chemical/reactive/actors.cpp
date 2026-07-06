#include "y/chemical/reactive/actors.hpp"
#include "y/exception.hpp"
#include "y/core/min.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        const char * const Actors:: CallSign = "Actors";

        Y_Proxy_Impl(Actors,list)

        Actors:: Actors(const Acting how) :
        Proxy<const Actor::List>(),
        Entity(),
        list(),
        acting(how)
        {
        }


        Actors:: ~Actors() noexcept
        {
        }


        bool Actors:: hired(const Species &sp) const noexcept
        {
            for(const Actor * a=list.head;a;a=a->next)
            {
                const Species &mine = a->sp;
                if( &sp == &mine ) return true;
            }
            return false;
        }

        void Actors:: hire(const unsigned int nu, const Species &sp)
        {
            const char * const id = sp.name.c_str();
            if(nu<=0)     throw Specific::Exception(CallSign, "zero stoechiometry for '%s'", id);
            if(hired(sp)) throw Specific::Exception(CallSign, "multiple '%s'", id);

            const Actor * const ac = list.pushTail( new Actor(nu,sp,acting) );
            try {
                String newName = name;
                if(list.size>1)
                {
                    switch(acting)
                    {
                        case AsSpec: newName += " + "; break;
                        case AsConc: newName += '+';   break;
                    }
                }
                newName += ac->name;
                Coerce(name).xch(newName);
            }
            catch(...) { delete list.popTail(); throw; }
        }

        void Actors:: massAction(XMul &X, const XReadable &C, const Level L) const
        {
            for(const Actor * a=list.head;a;a=a->next)
            {
                a->massAction(X,C,L);
            }
        }

        void Actors:: massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const
        {
            for(const Actor * a=list.head;a;a=a->next)
            {
                a->massAction(X,C,L,xi);
            }
        }

        apz  Actors:: charge() const
        {
            apz sumZ = 0;
            for(const Actor * a=list.head;a;a=a->next)
            {
                apz       z = a->sp.z;
                const apn n = a->nu;
                z *= n;
                sumZ += z;
            }

            return sumZ;
        }

        xreal_t Actors:: extent(const XReadable &C, const Level L) const noexcept
        {
            assert(list.size>0);
            const Actor *ac=list.head;
            xreal_t xi = ac->extent(C,L);
            for(ac=ac->next;ac;ac=ac->next)
                InSituMin(xi,ac->extent(C,L));
            return xi;
        }


        bool Actors:: active(const XReadable &C, const Level L) const noexcept
        {

            for(const Actor * ac=list.head;ac;ac=ac->next)
            {
                if( ac->sp(C,L) <= ac->zero ) return false;
            }
            return true;
        }

        void Actors:: safeMove(XWritable &C, const Level L, const xreal_t xi) const noexcept
        {
            for(const Actor * ac=list.head;ac;ac=ac->next)
            {
                ac->safeMove(C,L,xi);
            }
        }

        void Actors:: transfer(XWritable       &target, const Level tgt,
                               const XReadable &source, const Level src) const
        {
            for(const Actor * ac=list.head;ac;ac=ac->next)
            {
                const Species &sp = ac->sp;
                sp(target,tgt) = sp(source,src);
            }
        }

    }

}


#include "y/chemical/reactive/actors.hpp"
#include "y/exception.hpp"

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
                if(list.size>1) newName += " + ";
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

    }

}


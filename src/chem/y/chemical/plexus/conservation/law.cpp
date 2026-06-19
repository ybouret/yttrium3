
#include "y/chemical/plexus/conservation/law.hpp"
#include "y/string/format.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Law:: Law(const size_t i) noexcept :
            Actors(AsConc),
            irow(i),
            next(0),
            prev(0)
            {
            }

            Law:: ~Law() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Law &law)
            {
                return os << "d_(" << law.name << ")";
            }

            xreal_t Law:: excess(const XReadable &C, const Level L, XAdd &xadd) const
            {
                xadd.ldz();
                for(const Actor *ac=(**this).head;ac;ac=ac->next)
                {
                    const xreal_t acc = ac->xn * ac->sp(C,L);
                    xadd << acc;
                }
                return xadd();
            }

            namespace
            {
                static inline String actorHTML(const Actor &a)
                {
                    if(a.nu>1)
                    {
                        return Formatted::Get("%u",a.nu) + a.sp.makeHTML();
                    }
                    else
                    {
                        return a.sp.makeHTML();
                    }
                }
            }


            String Law:: html() const
            {
                assert( (**this).size >= 2);
                const Actor * ac=(**this).head; assert(ac);
                String        res = actorHTML(*ac);
                for(ac=ac->next;ac;ac=ac->next)
                {
                    res += '+' + actorHTML(*ac);
                }
                return res;
            }


            OutputStream & Law:: viz(OutputStream &     fp,
                                     const char * const color) const
            {
                nodeName(fp) << '[';
                {
                    const String label = html();
                    Label(fp,label);
                }
                if(color) fp << ",color=\"" << color << "\"";
                Endl(fp << ']');

                for(const Actor *ac=(**this).head;ac;ac=ac->next)
                {
                    to(&ac->sp,fp) << '[';
                    fp << "arrowhead=oinv";
                    if(color) fp << ",color=\"" << color << "\"";
                    Endl(fp << ']');
                }
                return fp;
            }



        }

    }

}



#include "y/chemical/plexus/conservation/law.hpp"
#include "y/string/format.hpp"
#include "y/stream/output.hpp"
#include "y/container/cxx/array.hpp"
#include "y/apex/api/simplify.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Law:: Law() noexcept :
            Actors(AsConc),
            gamma2(0),
            gamma(0),
            lproj(),
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

            bool Law:: linkedTo( const Law &law ) const noexcept
            {
                for(const Actor *ac=law->head;ac;ac=ac->next)
                {
                    if( hired(ac->sp) ) return true;
                }
                return false;
            }


            const char * const Law::Name = "Conservation::Law";

            void Law:: compile(XML::Log &xml, const SList &slist)
            {
                const Law &law = *this;
                Y_XML_Element_Attr(xml,Compile,Y_XML_Attr(law));
                const size_t  m  = slist->size;
                apn           g2 = 0;
                CxxArray<apn> gv(m);

                //--------------------------------------------------------------
                //
                //
                // accumulate gamma vector and its squared norm
                //
                //
                //--------------------------------------------------------------
                for(const Actor *ac=(**this).head;ac;ac=ac->next)
                {

                    const Species &sp = ac->sp; assert(slist.found(sp));
                    const apn      nu =  sp(gv,AuxLevel) = ac->nu;
                    g2 += nu * nu;
                }
                Y_XMLog(xml, "gamma2=" << g2);

                //--------------------------------------------------------------
                //
                //
                // compute factors
                //
                //
                //--------------------------------------------------------------
                {
                    unsigned ug2 = 0;
                    if(g2.is0())         throw Specific::Exception(Name,"invalid coefficients");
                    if(!g2.tryCast(ug2)) throw Specific::Exception(Name,"coefficients overflow");
                    Coerce(gamma2) = xreal_t(ug2);
                    Coerce(gamma)  = gamma2.sqrt();
                }

                //--------------------------------------------------------------
                //
                //
                // compute projection matrix
                //
                //
                //--------------------------------------------------------------
                Matrix<apz> p(m,m);
                for(size_t i=1;i<=m;++i)
                {
                    Writable<apz> &p_i = p[i];
                    for(size_t j=1;j<=m;++j)
                        Sign::MakeOpposite( Coerce( (p_i[j] = gv[i] * gv[j]).s ) );
                    p_i[i] += g2;
                }
                Y_XMLog(xml, "p=" << p << " / " << g2);

                {
                    const SNode *sn = slist->head;
                    for(size_t i=1;i<=m;++i,sn=sn->next)
                    {
                        const Species &sp    = **sn; if(!law.hired(sp)) continue;
                        Writable<apz> &numer = p[i];
                        apn            denom = g2;
                        Apex::Simplify::Array(numer,denom);
                        int          scal = 0; if(!denom.tryCast(scal)) throw Specific::Exception(Name,"scaling overflow");
                        Proj * const proj = Coerce(lproj).pushTail( new Proj(sp,scal) );
                        proj->build(slist,numer);
                        Y_XMLog(xml,*proj);

                    }
                }
            }

        }

    }

}


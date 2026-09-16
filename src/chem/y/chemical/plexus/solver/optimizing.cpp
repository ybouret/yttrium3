#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/type/temporary.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        void Solver:: upgrade(XML::Log & xml,
                              Ansatz   & a,
                              XTriplet & xx,
                              XTriplet & ff)
        {
            xreal_t x_opt;
            {
                const Temporary<bool> quiet(xml.verbose,false);
                x_opt = opt.find(xml,*this,Minimize::Direct,xx,ff,Minimize::Standard);
            }
            Y_XMLog(xml, "[+] F(" << x_opt.str() <<") = " << ff.b );
            a.F1 = ff.b;
            a.cc.load(Ctry);
        }


        bool Solver:: optimizing(XML::Log     & xml,
                                 Ansatz       & a,
                                 const xreal_t  F0,
                                 const size_t   i)
        {
            //------------------------------------------------------------------
            //
            // initialize Cend at 1D solution
            //
            //------------------------------------------------------------------
            const String &eid = a.eq.name;
            Y_XML_Element_Attr(xml,Optimizing, Y_XML_Attr(eid) );
            Solver &self = *this;
            Cend.load(a.cc);
            const xreal_t  F1 = F(Cend,SubLevel);
            Y_XMLog(xml,"F(0)   = " << self(0).str() << " / " << F0.str() );
            Y_XMLog(xml,"F(1)   = " << self(1).str() << " / " << F1.str() );
            Coerce(a.F1) = F1;


            if(Trace)
            {
                const String bn = MakeFileName(a.eq.name);
                const String fn = bn + '.' + StdProfileExt;
                OutputFile   fp(fn);
                saveProfile(fp,1000);
                {
                    if(1==i)
                        trace += "plot ";
                    else
                        trace += ", ";
                    trace += ("'" + fn + "' w l");
                }
            }

            // study cases
            XTriplet xx = {  0, MKL::Numeric<xreal_t>::HALF, 1 };
            XTriplet ff = { F0, self(xx.b), F1 };
            Y_XMLog(xml,"F(1/2) = " << ff.b.str() );

            // assuming true result
            bool result = true;
            if(F1<F0)
            {
                // directly ok!
                if(ff.b<F1)
                {
                    // and upgradable
                    upgrade(xml,a,xx,ff);
                    Y_XMLog(xml, "[++] " << a.F1.str() << " @" << a.eq.name);
                }
                else
                {
                    Y_XMLog(xml, "[+]  " << a.F1.str() << " @" << a.eq.name);
                }

                assert(true==result);
            }
            else
            {
                assert(F1>=F0);
                // not ok
                if(ff.b<F0)
                {
                    // but upgradable
                    upgrade(xml,a,xx,ff);
                    assert(true==result);
                    Y_XMLog(xml, "[-+] " << a.F1.str() << " @" << a.eq.name);
                }
                else
                {
                    Y_XMLog(xml, "[-]  " << a.F1.str() << " @" << a.eq.name);
                    result = false;
                }
            }

            if(Trace)
            {
                Cend.load(a.cc);
                const String fn = MakeFileName(a.eq.name) + '.' + OptProfileExt;
                OutputFile   fp(fn);
                saveProfile(fp,1000);
                {
                    if(1==i)
                        tropt += "plot ";
                    else
                        tropt += ", ";
                    tropt += ("'" + fn + "' w l");
                }
            }

            return result;

        }
    }

}

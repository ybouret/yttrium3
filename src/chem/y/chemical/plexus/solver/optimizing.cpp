#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/type/temporary.hpp"
#include "y/mkl/minimize/golden.hpp"

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
            // Initialize Cend at 1D solution, and deduce F1
            //
            //------------------------------------------------------------------
            const String &eid = a.eq.name;
            Y_XML_Element_Attr(xml,Optimizing, Y_XML_Attr(eid) );
            Solver &self = *this;
            Cend.load(a.cc);
            const xreal_t  F1 = F(Cend,SubLevel);
            Y_XMLog(xml,"F(0) = " << self(0).str() << " / " << F0.str() );
            Y_XMLog(xml,"F(1) = " << self(1).str() << " / " << F1.str() );
            a.F1 = F1;



            //------------------------------------------------------------------
            //
            // Emit Initial Profile
            //
            //------------------------------------------------------------------
            if(Trace)
            {
                const String bn = MakeFileName(a.eq.name);
                const String fn = bn + '.' + StdProfileExt;
                OutputFile   fp(fn);
                saveProfile(fp,TracePoints);
                {
                    if(1==i)
                        trace += "plot ";
                    else
                        trace += ", ";
                    trace += ("'" + fn + "' w l");
                }
            }
            

            //------------------------------------------------------------------
            //
            // Study Result
            //
            //------------------------------------------------------------------
            XTriplet xx = { MKL::Numeric<xreal_t>::ZERO, MKL::Numeric<xreal_t>::ZERO, MKL::Numeric<xreal_t>::ONE };
            XTriplet ff = { F0, F0, F1 };
            bool     result = true;
            if(F1<F0)
            {
                //--------------------------------------------------------------
                // global decrease
                //--------------------------------------------------------------
                ff.b = self( xx.b = MKL::Numeric<real_t>::GOLDEN_R );
                Y_XMLog(xml,"F(R) = " << ff.b.str() );

                if(ff.b<F1)
                {
                    // still upgradable
                    upgrade(xml,a,xx,ff);
                    Y_XMLog(xml, "[++] " << a.F1.str() << " @" << a.eq.name);
                }
                else
                {
                    // assume global minimun
                    Y_XMLog(xml, "[+]  " << a.F1.str() << " @" << a.eq.name);
                }

            }
            else
            {
                //--------------------------------------------------------------
                //
                //--------------------------------------------------------------
                ff.b = self( xx.b = MKL::Numeric<real_t>::GOLDEN_C );
                Y_XMLog(xml,"F(C) = " << ff.b.str() );
                if(ff.b<F0)
                {
                    // but upgradable
                    upgrade(xml,a,xx,ff);
                    assert(true==result);
                    Y_XMLog(xml, "[-+] " << a.F1.str() << " @" << a.eq.name);
                }
                else
                {
                    // assume wrong direction
                    Y_XMLog(xml, "[-]  " << a.F1.str() << " @" << a.eq.name);
                    result = false;
                }
            }

            


            if(Trace)
            {
                Cend.load(a.cc);
                const String fn = MakeFileName(a.eq.name) + '.' + OptProfileExt;
                OutputFile   fp(fn);
                saveProfile(fp,TracePoints);
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

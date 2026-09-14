#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/type/temporary.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool Solver:: optimizing(XML::Log     & xml,
                                 const Ansatz & a,
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


            
            if(Trace)
            {
                const String fn = MakeFileName(a.eq.name) + ".ycp";
                OutputFile   fp(fn);
                saveProfile(fp,10000);
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

            if(F1<F0)
            {
                Y_XMLog(xml, "[+]");
                // directly ok!
                if(ff.b<F1)
                {
                    const bool    flag = xml.verbose; //xml.verbose = false;
                    const xreal_t x_opt = opt.find(xml,self,Minimize::Direct,xx,ff,Minimize::Standard);
                    xml.verbose = flag;
                    Y_XMLog(xml, "[++] F(" << x_opt.str() <<") = " << ff.b );
                }


            }
            else
            {
                assert(F1>=F0);
                Y_XMLog(xml, "[-]");

            }




            return true;

            //const xreal_t x_opt = opt.find(xml,self,Minimize::Inside,xx,ff,Minimize::Standard);

            return true;
        }
    }

}

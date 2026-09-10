#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"


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
            Solver &self = *this;
            Cend.load(a.cc);
            const xreal_t  F1 = F(Cend,SubLevel);
            Y_XMLog(xml,"F(0) = " << self(0).str() << "/" << F0.str() );
            Y_XMLog(xml,"F    = " << F1.str() <<  " @" << a.eq);
            Y_XMLog(xml,"F(1) = " << self(1).str() );


            if(Trace)
            {
                const String fn = MakeFileName(a.eq.name) + ".ycp";
                OutputFile   fp(fn);
                saveProfile(fp,500);

                {
                    if(1==i)
                        trace += "plot ";
                    else
                        trace += ", ";
                    trace += ("'" + fn + "' w l");
                }
            }

            
            // study cases
            XTriplet xx = {  0, 0.5,         1 };
            XTriplet ff = { F0, self(xx.b), F1 };

            Y_XMLog(xml,ff.a.str() << " -> " << ff.b.str() << " -> " << ff.c.str() );

            const xreal_t x_opt = opt.find(xml,self,Minimize::Inside,xx,ff,Minimize::Standard);




            return true;
        }
    }

}

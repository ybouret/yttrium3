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
            Cend.load(a.cc); // initialize Cend at 1D solution
            const xreal_t  Fi = F(Cend,SubLevel);
            Y_XMLog(xml,"F = " << Fi.str() <<  " @" << a.eq);

            if(Trace)
            {
                const String fn = MakeFileName(a.eq.name) + ".ycp";
                OutputFile   fp(fn);
                saveProfile(fp,500);

                {
                    OutputFile fp("solver.gp",true);
                    if(1==i)
                        fp << "plot ";
                    else
                        fp << ", ";
                    fp << "'" << fn << "' w l";
                    if(i==ans.size()) fp << '\n';
                }

            }

        }
    }

}

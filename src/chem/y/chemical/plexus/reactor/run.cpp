#include "y/chemical/plexus/reactor.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        static inline
        const char * HRConverged(const bool flag) noexcept
        {
            return flag ?
            "[converged]" :
            "[separated]";
        }

        Reactor::Outcome Reactor:: run(XML::Log &xml, XWritable &C, const Level L, const XReadable &K)
        {
            Y_XML_Element(xml,ReactorRun);

            //------------------------------------------------------------------
            //
            //
            // initialize for consistency
            //
            //
            //------------------------------------------------------------------
            F0.ldz();
            basis.free();

            //------------------------------------------------------------------
            //
            //
            // build RUNNING assays, tweaking C if crucial equilibria are met
            //
            //
            //------------------------------------------------------------------
            const size_t na = buildAssays(xml,C,L,K);
            Y_XMLog(xml,"#assay = " << na);
            if(na<=0)
            {
                return Achieved;
            }

            //------------------------------------------------------------------
            //
            //
            // Initialize from 1D assays
            //
            //
            //------------------------------------------------------------------
            Indexed::Transfer(Cini,SubLevel,C,L,cluster.slist);
            F0 = Fs = ObjectiveFunction(Cini,SubLevel);
            Y_XMLog(xml,"F0 = " << F0.str());

            //------------------------------------------------------------------
            //
            //
            // Study and optimize assays
            //
            //
            //------------------------------------------------------------------
            const size_t        ok     = studyAssays(xml);
            const Assay * const best1D = (ok<=0) ? 0 : & assays[1];
            if(best1D)
            {
                Y_XMLog(xml, "[best1D] " << best1D->F1.str() << " @" << best1D->eq.name);
            }
            else
            {
                Y_XMLog(xml, "[best1D] NONE");
            }

            //------------------------------------------------------------------
            //
            //
            // create local basis
            //
            //
            //------------------------------------------------------------------
            createBasis(xml);

            //------------------------------------------------------------------
            //
            //
            // Newton Raphson step
            //
            //
            //------------------------------------------------------------------
            const bool hasNRS = builtNRStep(xml);
            if(hasNRS)
            {
                Y_XMLog(xml, "[hasNRS] " << Fs.str() );
            }
            else
            {
                Y_XMLog(xml, "[hasNRS] NONE");
            }

            if(TracePro)
            {
                std::cerr << gpStd << std::endl;
                std::cerr << gpOpt << std::endl;
            }

            //------------------------------------------------------------------
            //
            //
            // Select best solution
            //
            //
            //------------------------------------------------------------------
            const bool with1D    = best1D;
            const bool withNR    = hasNRS;
            bool       converged = false;



            Y_XML_Element_Attr(xml,SelectStep,Y_XML_Attr(with1D) << Y_XML_Attr(withNR) );
            if(best1D)
            {
                const xreal_t F1 = best1D->F1;
                Y_XMLog(xml, "@best1D: " << F1.str() );
                assert(F1<F0);
                //--------------------------------------------------------------
                //
                // GOT a best1D
                //
                //--------------------------------------------------------------
                if(hasNRS)
                {
                    //----------------------------------------------------------
                    //
                    // AND Newton-Raphson Step
                    //
                    //----------------------------------------------------------
                    Y_XMLog(xml, "@hasNRS: " << Fs.str() ); assert(Fs<F0);

                    if(Fs<=F1)
                    {
                        converged = convergence(C,L,Cend,SubLevel);
                        Indexed::Transfer(C,L,Cend,SubLevel,cluster.slist);
                        Y_XMLog(xml, "|_useNR " << HRConverged(converged) );
                    }
                    else
                    {
                        converged = convergence(C,L,best1D->cc,SubLevel);
                        Indexed::Transfer(C,L,best1D->cc,SubLevel,cluster.slist);
                        Fs = F1;
                        Y_XMLog(xml, "|_use1D " << HRConverged(converged) );

                    }
                }
                else
                {
                    //----------------------------------------------------------
                    //
                    // BUT NO Newton-Raphson Step
                    //
                    //----------------------------------------------------------
                    converged = convergence(C,L,best1D->cc,SubLevel);
                    Indexed::Transfer(C,L,best1D->cc,SubLevel,cluster.slist);
                    Fs = F1;
                    Y_XMLog(xml, "|_use1D " << HRConverged(converged) );

                }

                return Fs.mantissa <= 0 ? Achieved : Improved;
            }
            else
            {
                //--------------------------------------------------------------
                //
                // NO best1D
                //
                //--------------------------------------------------------------
                if(hasNRS)
                {
                    //----------------------------------------------------------
                    //
                    // BUT GOT Newton-Raphson Step
                    //
                    //----------------------------------------------------------
                    converged = convergence(C,L,Cend,SubLevel);
                    Indexed::Transfer(C,L,Cend,SubLevel,cluster.slist);
                    Y_XMLog(xml, "@hasNRS: " << Fs.str() << " " << HRConverged(converged) ); assert(Fs<F0);
                    return Fs.mantissa <= 0 ? Achieved : Improved;
                }
                else
                {
                    //----------------------------------------------------------
                    //
                    // Got nothing better
                    //
                    //----------------------------------------------------------
                    Y_XMLog(xml, "[-- stall --]");
                    return F0.mantissa <= 0 ? Achieved : Spurious;
                }
            }


        }

    }

}


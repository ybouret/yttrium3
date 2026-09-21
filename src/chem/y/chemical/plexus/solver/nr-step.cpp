#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool Solver:: NRStep(XML::Log        & xml,
                             const xreal_t     F0,
                             const XReadable & C,
                             const Level       L)
        {
            Y_XML_Element(xml,NewtonRaphson);
            //Y_XMLog(xml, "F0=" << F0.str());

            /**/ if(!computeStep(xml,C,L)) return false;
            /**/     approveStep(xml);


            const xreal_t F1 = F(Cend,SubLevel);
            Y_XMLog(xml, "F0=" << F0.str());
            Y_XMLog(xml, "F1=" << F1.str());

            if(Trace)
            {
                OutputFile fp("nr-step.ycp");
                saveProfile(fp,TracePoints);
                trace += ",'nr-step.ycp' w l";
            }

            Solver &self = *this;
            bool    result = true;
            if(F1<F0)
            {
                // winning, check if optimization is required
                Y_XMLog(xml, "-- winning");

                XTriplet xx = { MKL::Numeric<xreal_t>::ZERO, MKL::Numeric<xreal_t>::GOLDEN_R, MKL::Numeric<xreal_t>::ONE };
                XTriplet ff = { F0, self(xx.b), F1 };
                Y_XMLog(xml, "FR=" << ff.b.str() );
                if(ff.b<F1)
                {
                    Y_XMLog(xml, "-- use corrected");
                }
                else
                {
                    Y_XMLog(xml, "-- use predicted");
                }

            }
            else
            {
                // loosing, check if possible optimization
                Y_XMLog(xml, "-- loosing");
                XTriplet xx = { MKL::Numeric<xreal_t>::ZERO, MKL::Numeric<xreal_t>::GOLDEN_C, MKL::Numeric<xreal_t>::ONE };
                XTriplet ff = { F0, self(xx.b), F1 };
                Y_XMLog(xml, "FC=" << ff.b.str() );
                if(ff.b<F0)
                {
                    Y_XMLog(xml, "-- use corrected");

                    assert(true==result);
                }
                else
                {
                    Y_XMLog(xml, "-- no improvement");
                    result = false;
                }
            }




            return result;
        }
    }
}

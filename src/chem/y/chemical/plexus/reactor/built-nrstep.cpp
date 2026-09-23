
#include "y/chemical/plexus/reactor.hpp"
#include "y/stream/libc/output.hpp"
#include "y/type/temporary.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace
        {
            static inline
            void OptimizeNR(XML::Log & xml,
                            Reactor  & F,
                            XTriplet & xx,
                            XTriplet & ff)
            {
                xreal_t xopt;
                {
                    const Temporary<bool> quiet(xml.verbose,false);
                    assert(xx.isIncreasing());
                    assert(ff.isLocalMinimum());
                    xopt = F.resources->minimize.find(xml,F, MKL::Minimize::Direct, xx, ff, MKL::Minimize::Standard);
                }
                Y_XMLog(xml, "[+] F(" << xopt.str() <<") = " << ff.b.str() );
                F.Cend.load(F.Ctry);
            }
        }


        bool Reactor:: builtNRStep(XML::Log &xml)
        {
            Y_XML_Element(xml,NewtonRaphson);
            if( !computeStep(xml) ) return false;
            /**/ approveStep(xml);

            if(TracePro)
            {
                OutputFile fp("nr-step.ycp");
                saveProfile(fp);
                gpStd += ",'nr-step.ycp' w l";
            }

            Y_XMLog(xml, "F0 = " << F0.str() );
            Y_XMLog(xml, "Fs = " << Fs.str() );
            

            //------------------------------------------------------------------
            //
            // check status of predicted point
            //
            //------------------------------------------------------------------
            Reactor &self   = *this;
            bool    result = true;
            if(Fs<F0)
            {
                //--------------------------------------------------------------
                //
                // winning, check if optimization is required
                //
                //--------------------------------------------------------------
                Y_XMLog(xml, "-- winning");

                XTriplet xx = { MKL::Numeric<xreal_t>::ZERO, MKL::Numeric<xreal_t>::GOLDEN_R, MKL::Numeric<xreal_t>::ONE };
                XTriplet ff = { F0, self(xx.b), Fs };
                Y_XMLog(xml, "FR=" << ff.b.str() );
                if(ff.b<Fs)
                {
                    Y_XMLog(xml, "-- use corrected");
                    OptimizeNR(xml,self,xx,ff);
                    Fs = ff.b;
                    assert(Fs<F0);
                }
                else
                {
                    Y_XMLog(xml, "-- use predicted");
                    assert(Fs<F0);
                }
                assert(true==result);
            }
            else
            {
                //--------------------------------------------------------------
                //
                // loosing, check if possible last resort optimization
                //
                //--------------------------------------------------------------
                Y_XMLog(xml, "-- loosing");
                XTriplet xx = { MKL::Numeric<xreal_t>::ZERO, MKL::Numeric<xreal_t>::GOLDEN_C, MKL::Numeric<xreal_t>::ONE };
                XTriplet ff = { F0, self(xx.b), Fs };
                Y_XMLog(xml, "FC=" << ff.b.str() );
                if(ff.b<F0)
                {
                    Y_XMLog(xml, "-- use corrected");
                    OptimizeNR(xml,self,xx,ff);
                    Fs = ff.b;
                    assert(Fs<F0);
                    assert(true==result);
                }
                else
                {
                    Y_XMLog(xml, "-- no improvement");
                    assert(Fs>=F0);
                    result = false;
                }

            }

            if(TracePro)
            {
                OutputFile fp("nr-step.yop");
                saveProfile(fp);
                gpOpt += ",'nr-step.yop' w l";
            }

            return result;
        }
    }

}



#include "y/chemical/plexus/reactor.hpp"
#include "y/core/hsort.hpp"
#include "y/stream/libc/output.hpp"
#include "y/type/temporary.hpp"
#include "y/mkl/minimize/golden.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        void   Reactor:: updateAssay(XML::Log & xml,
                                     Assay    & assay,
                                     XTriplet & xx,
                                     XTriplet & ff)
        {
            assert(xx.isIncreasing());
            assert(ff.isLocalMinimum());
            xreal_t xopt;
            {
                const Temporary<bool> quiet(xml.verbose,false);
                xopt = MKL::Golden<xreal_t>::Find(xml, *this, xx, ff);
            }
            Y_XMLog(xml, "|_F(" << xopt <<") = " << ff.b);
            assay.F1 = ff.b;
            assay.cc.load(Ctry);
        }


        namespace
        {
            static inline
            SignType CompareAssays(const Assay &lhs, const Assay &rhs) noexcept
            {
                return Sign::Of(lhs.F1,rhs.F1);
            }
        }

        size_t Reactor:: studyAssays(XML::Log &xml)
        {
            const size_t na = assays.size(); assert(na>0);
            Y_XML_Element_Attr(xml,StudyAssays, Y_XML_Attr(na));
            size_t       ok = 0;

            if(TracePro)
            {
                gpStd = "plot ";
                gpOpt = "plot ";
            }

            for(size_t i=1;i<=na;++i)
            {
                Assay        & assay = assays[i];
                const String & eid   = assay.eq.name;
                Y_XML_Element_Attr(xml,Study,Y_XML_Attr(eid));

                // load end point
                Cend.load(assay.cc);
                if(TracePro)
                {
                    const String fn = MakeFileName(eid) + '.' + StdProfileExt;
                    OutputFile   fp(fn);
                    saveProfile(fp);
                    if(i>1) {
                        gpStd += ',';
                    }
                    gpStd += "'" + fn + "' w l";
                }

                // full objective function at 1D solution
                xreal_t & F1 = (assay.F1 = ObjectiveFunction(Cend,SubLevel));
                Y_XMLog(xml, "F0 = " << F0.str());
                Y_XMLog(xml, "F1 = " << F1.str() << " @" << assay.eq.name);

                Reactor &F = *this;
                if(F1<F0)
                {
                    Y_XMLog(xml, "|_ready");
                    XTriplet xx = { MKL::Numeric<xreal_t>::ZERO, MKL::Numeric<xreal_t>::GOLDEN_R, MKL::Numeric<xreal_t>::ONE };
                    XTriplet ff = { F0, F(xx.b), F1 };
                    if(ff.b<F1)
                    {
                        // optimize furthermore
                        Y_XMLog(xml, "|_optimize");
                        assert(xx.isIncreasing());
                        assert(ff.isLocalMinimum());
                        updateAssay(xml,assay,xx,ff);
                    }
                    else
                    {
                        // 1D solution is assumed optimal
                        Y_XMLog(xml, "|_overall");
                    }
                    ++ok;
                }
                else
                {
                    Y_XMLog(xml, "|_stall");
                    XTriplet xx = { MKL::Numeric<xreal_t>::ZERO, MKL::Numeric<xreal_t>::GOLDEN_C, MKL::Numeric<xreal_t>::ONE };
                    XTriplet ff = { F0, F(xx.b), F1 };
                    if(ff.b<F0)
                    {
                        // backtrack
                        Y_XMLog(xml, "|_backtrack");
                        assert(xx.isIncreasing());
                        assert(ff.isLocalMinimum());
                        updateAssay(xml,assay,xx,ff);
                        ++ok;
                    }
                    else
                    {
                        // discard
                        Y_XMLog(xml, "|_discard");
                        F1 = F0;
                        assay.cc.load(Cini);
                    }
                }
            }

            Y_XMLog(xml, "ok = " << ok << " / " << na);
            Y_XMLog(xml, "F0 = " << F0.str());
            Core::HSort::Make( & assays[1], na, CompareAssays );
            for(size_t i=1;i<=na;++i)
            {
                const Assay  &assay = assays[i];
                const String &eid   = assay.eq.name;
                const char * sfx    = "";
                if(i>ok)     sfx    = " (stalled)";
                Y_XMLog(xml, "F1 = " << assay.F1.str() << " @" << eid << sfx);

                if(TracePro)
                {
                    Cend.load(assay.cc);
                    const String fn = MakeFileName(eid) + '.' + OptProfileExt;
                    OutputFile   fp(fn);
                    saveProfile(fp);
                    if(i>1) {
                        gpOpt += ',';
                    }
                    gpOpt += "'" + fn + "' w l";
                }

            }

          
            return ok;
        }
    }

}



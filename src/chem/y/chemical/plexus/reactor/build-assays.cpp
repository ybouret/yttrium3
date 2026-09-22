
#include "y/chemical/plexus/reactor.hpp"
#include "y/core/hsort.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        size_t Reactor:: buildAssays(XML::Log &xml, XWritable &C, const Level L, const XReadable &K)
        {
            Y_XML_Element_Attr(xml,BuildAssays,Y_XML_Attr(n));

        BUILD:
            assays.free();
            bool emergency = false;
            for(const ENode *en=cluster.elist->head;en;en=en->next)
            {
                const Equilibrium &eq = **en;
                const xreal_t      eK = eq(K,TopLevel);
                XWritable         &cc = Indexed::Transfer(Ceq[ assays.size() + 1],SubLevel,C,L,cluster.slist);
                const Aftermath    am = Aftermath::Compute(xml,cc,SubLevel,C,L,eq,eK,xmul,xadd);
                switch(am.st)
                {
                    case Blocked:
                        continue;

                    case Running:
                        if(emergency) continue;
                        break;

                    case Crucial:
                        emergency = true;
                        break;
                }

                const Assay assay(eq,eK,am,cc);
                assays << assay;
            }

            if(emergency)
            {
                Y_XML_Element(xml,Emergency);
                assert(assays.size()>0);

                // remove running
                for(size_t i=assays.size();i>0;)
                {
                    switch( assays[i].am.st )
                    {
                        case Blocked: throw Specific::Exception("Reactor::buildAssays","corrupted code");
                        case Running: assays.remove(i); break;
                        case Crucial: --i; break;
                    }
                }

                // sort crucial
                assert(assays.size()>0);
                Core::HSort::Make(&assays[1], assays.size(), Assay::IncreasingAX);
                for(size_t i=1;i<=assays.size();++i)
                {
                    const Assay &assay = assays[i]; assert(Crucial==assay.am.st);
                    Y_XMLog(xml,
                            "[-] nz="  << std::setw(3)   << assay.am.nz
                            << " | xi=" << std::setw(22) << assay.am.xi.str()
                            << " @ " << assay.eq.name );
                }

                // move C to selected crucial
                Indexed::Transfer(C,L,assays[1].cc,SubLevel,cluster.slist);
                goto BUILD;
            }


            const size_t na = assays.size();
            if(na>0)
            {
                for(size_t i=assays.size();i>0;--i)
                {
                    const Assay &assay = assays[i]; assert(Running==assay.am.st);
                    Coerce(assay.A0) = assay.affinity(C,L,xadd);
                }

                Core::HSort::Make(&assays[1], assays.size(), Assay::DecreasingAA);

                if(xml.verbose)
                {

                    for(size_t i=1;i<=na;++i)
                    {
                        const Assay &assay = assays[i];
                        xml()
                        << "[+] A0 = " << assay.A0.str()
                        <<" |  xi = "  << assay.am.xi.str()
                        << " @ " << assay.eq.name
                        << std::endl;
                    }
                }

                return assays.size();
            }
            else
                return 0;
        }

    }

}


#include "y/chemical/plexus/combinatorics/mixed.hpp"
#include "y/string/format.hpp"
namespace Yttrium
{
    namespace Chemical
    {

        namespace
        {
            static String FirstCoeff(const int w)
            {
                assert(w);
                switch(w)
                {
                    case  1: return  "";
                    case -1: return '-';
                    default:
                        break;
                }
                return Formatted::Get("%d*",w);
            }

            static String ExtraCoeff(const int w)
            {
                assert(w);
                switch(w)
                {
                    case  1: return '+';
                    case -1: return '-';
                    default:
                        break;
                }
                return Formatted::Get("%+d*",w);
            }


        }

        String MixedEquilibrium:: MakeName(const EList &elist,
                                           const IList &ilist)
        {
            assert(elist->size==ilist->size);
            assert(elist->size>0);
            String res;

            const ENode *en = elist->head; assert(en);
            const INode *in = ilist->head; assert(in);

            res += FirstCoeff(**in);
            res += (**en).name;
            for(en=en->next,in=in->next;en;en=en->next,in=in->next)
            {
                assert(en); assert(in);
                res += ExtraCoeff(**in);
                res += (**en).name;
            }



            return res;
        }

        MixedEquilibrium:: ~MixedEquilibrium() noexcept
        {

        }


        MixedEquilibrium:: MixedEquilibrium(const String    & eqName,
                                            const size_t      eqIndx,
                                            const EList     & elist,
                                            const IList     & ilist,
                                            const XReadable & Karray) :
        Equilibrium(eqName,eqIndx),
        itop(elist->size),
        coef(ilist),
        numer(),
        denom(),
        topK( Karray )
        {
            assert(elist->size==ilist->size);
            {
                size_t ei = 1;
                for(const ENode *en=elist->head;en;en=en->next,++ei)
                {
                    Coerce(itop[ei]) = (**en).indx[TopLevel];
                }
            }

        }


        MixedEquilibrium * MixedEquilibrium:: Create(const size_t      eqIndx,
                                                     const EList     & emx,
                                                     const IList     & ecf,
                                                     const SList     & smx,
                                                     const IList     & scf,
                                                     const XReadable & Karray)
        {
            // create equilibrium
            const String             mxName = MakeName(emx,ecf);
            MixedEquilibrium * const mx     = new MixedEquilibrium(mxName,eqIndx,emx,ecf,Karray);

            // populate
            assert(smx->size==scf->size);
            
            mx->freeze();
            return mx;
        }

        xreal_t MixedEquilibrium:: getK(const xreal_t)
        {

        }


    }

}



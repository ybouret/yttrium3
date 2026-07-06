#include "y/chemical/plexus/conservations.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Proj:: ~Proj() noexcept
            {
            }

            Proj:: Proj(const Species &sp_, const xreal_t sc_) noexcept :
            Object(), PCoef::List(),
            sp(sp_),
            scal(sc_),
            next(0),
            prev(0)
            {
            }

            std::ostream & operator<<(std::ostream &os, const Proj &proj)
            {
                const PCoef::List &self = proj;
                os << '[' << proj.sp << ']' << " : " << self << "/" << (double)proj.scal;
                return os;
            }

            void Proj:: build(const SList         &species,
                              const Readable<apz> &weights)
            {
                const size_t m = species->size; assert(species->size==weights.size());
                const SNode *sn = species->head;
                for(size_t i=1;i<=m;++i,sn=sn->next)
                {
                    const apz &   W  = weights[i]; if(W.is0()) continue;
                    int           w  = 0;          if(!W.tryCast(w)) throw Specific::Exception(Law::Name,"projection weight overflow!!");
                    pushTail( new PCoef(w,**sn) );
                }
            }
        }
    }
}

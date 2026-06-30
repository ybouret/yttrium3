

#include "y/chemical/plexus/conservation/canon.hpp"
//#include "y/mkl/algebra/rank.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Canon:: ~Canon() noexcept
            {
            }

            Canon:: Canon(const Law &first) :
            Object(),
            species( new SpRoll() ),
            laws(),
            next(0),
            prev(0),
            //Gamma(),
            //rg(0),
            lfmt()
            {
                laws.pushTail(first);
            }

            bool Canon:: accepts(const Law &law) const noexcept
            {
                for(const LNode *ln=laws->head;ln;ln=ln->next)
                {
                    if( (**ln).linkedTo(law) ) return true;
                }
                return false;
            }

            void Canon:: compile()
            {
                // initialize
                species->free();
                lfmt.reset();

                // build species
                for(const LNode *ln=laws->head;ln;ln=ln->next)
                {
                    const Law &law = **ln;
                    lfmt.enroll(law);
                    for(const Actor *ac=law->head;ac;ac=ac->next)
                    {
                        species->inscribe(ac->sp);
                    }
                }
                Indexed::AuxLabel( Indexed::TopHSort( Coerce(species->list) ) );

                for(const LNode *ln=laws->head;ln;ln=ln->next)
                    Coerce( **ln ).compile(species->list);


#if 0
                const size_t Nc = laws->size; assert(Nc>0);
                const size_t M  = species->list->size;
                Gamma.make(Nc,M);
                size_t i = 1;
                for(const LNode *ln=laws->head;ln;ln=ln->next,++i)
                {
                    const Law &law = **ln;
                    for(const Actor *ac=law->head;ac;ac=ac->next)
                    {
                        ac->sp(Gamma[i],AuxLevel) = ac->nu;
                    }
                }
                rg = MKL::Rank::Of(Gamma);
#endif
            }

        }

    }

}

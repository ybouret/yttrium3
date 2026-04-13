
//! \file

#ifndef Y_Apex_KegDec_Included
#define Y_Apex_KegDec_Included 1

#include "y/apex/k/div.hpp"


namespace Yttrium
{
    namespace Apex
    {

        struct KegDec
        {
            template <typename WORD, typename CORE> static inline
            String ToString(const Keg<WORD> &value)
            {
                //std::cerr << "#words=" << value.words << std::endl;

                
                if(value.bits<=0)
                    return '0';
                else
                {
                    const WORD ten = 10;
                    String     res;
                    AutoPtr< Keg<WORD> > q,r,n = new Keg<WORD>(value);

                    {
                    NEXT_CHAR:
                        KegDiv::Compute<WORD,CORE>(&q, &r, n->word, n->words, &ten, 1);
                        //std::cerr << "r=" << r << std::endl;
                        assert(r.isValid());
                        assert(q.isValid());
                        assert(r->words<=1);
                        assert(r->word[0]<ten);
                        //std::cerr << "n=" << n << " | q=" << q << " | r= " << r << std::endl;
                        res += '0' + r->word[0];
                        if(q->bits)
                        {
                            n.xch(q);
                            goto NEXT_CHAR;
                        }
                    }

                    res.reverse();
                    return res;
                }
            }

        };

    }

}

#endif // !Y_Apex_KegDec_Included

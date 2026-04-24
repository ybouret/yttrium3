
#include "y/apex/n/modular.hpp"
#include "y/apex/integer.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Apex
    {
        
        Natural Modular::Exp(const Natural &b,
                             const Natural &e,
                             const Natural &modulus)
        {

            Natural base     = b;
            Natural exponent = e;

            Natural result   = 1;
            base %= modulus;
            while(exponent.bits()>0)
            {
                if(exponent.isOdd())
                    result = (result * base) % modulus;
                exponent.shr();
                base = base.mod2() % modulus;
            }
            return result % modulus;
        }

        Natural Modular::Inv(const Natural &a, const Natural &n)
        {
            Integer t=0,newt=1;
            Natural r=n,newr=a;


            while(newr.bits()>0)
            {
                Natural quotient;
                Natural remainder;
                Natural::Division( &quotient, &remainder, r, newr);
                {
                    Integer _ = t - quotient * newt;
                    t.xch(newt);
                    newt.xch(_);
                }
                r.xch(newr);
                newr.xch(remainder);
            }

            if(r>1)
                throw Specific::Exception("Modular::Inv","Singular Value");

            while(t.s != Positive) t += n;
            return t.n;
        }

    }

}



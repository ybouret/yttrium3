#include "y/apex/integer.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {

        Integer Integer::Div(const Integer &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.s,rhs.s) )
            {

                case Sign::NN:
                case Sign::PP:
                    return Natural::Div(lhs.n,rhs.n);

                case Sign::NP:
                case Sign::PN: {
                    const Natural q = Natural::Div(lhs.n,rhs.n);
                    if(q.bits()) return Integer(Negative,q); else return Integer();
                }



                case Sign::NZ:
                case Sign::PZ:
                case Sign::ZZ:
                    throw Libc::Exception(EDOM,"%s division by zero (Integer/Integer)", CallSign);

                case Sign::ZN:
                case Sign::ZP:
                    break; // => zero
            }
            return 0;
        }

        Integer Integer:: Div(const Integer &lhs, const Natural &rhs)
        {

            if( rhs.bits() <= 0 )
            {
                throw Libc::Exception(EDOM,"%s division by zero (Integer/Natural)", CallSign);
            }

            switch(lhs.s)
            {
                case Negative: {
                    const Natural q = Natural::Div(lhs.n,rhs);
                    if(q.bits()) return Integer(Negative,q); else return Integer();
                }
                case Positive: return Natural::Div(lhs.n,rhs);
                case __Zero__:
                    break; // => zero
            }
            return Integer();
        }

        Integer Integer:: Div(const Natural &lhs, const Integer &rhs)
        {

            switch(rhs.s)
            {
                case Negative: {
                    const Natural q = Natural::Div(lhs,rhs.n);
                    if(q.bits()) return Integer(Negative,q); else return Integer();
                }
                case Positive: return Natural::Div(lhs,rhs.n);
                case __Zero__: break;
            }
            throw Libc::Exception(EDOM,"%s division by zero (Natural/Integer)", CallSign);
        }


    }

}

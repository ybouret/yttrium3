
#include "y/jive/pattern/all.hpp"

namespace Yttrium
{
    namespace Jive
    {
        bool Pattern:: AreEqual(const Pattern &lhs, const Pattern &rhs) noexcept
        {
            const uint32_t uid = lhs.uuid;
            if(uid!=rhs.uuid) return false;

            switch(uid)
            {
                case Any1:: UUID: return true;
                case Byte:: UUID: return dynamic_cast<const Byte &>(lhs).code == dynamic_cast<const Byte &>(rhs).code;
                case Excl:: UUID: return dynamic_cast<const Excl &>(lhs).code == dynamic_cast<const Excl &>(rhs).code;
                case Lump:: UUID: {
                    const Lump &L = dynamic_cast<const Lump&>(lhs);
                    const Lump &R = dynamic_cast<const Lump&>(rhs);
                    return L.lower == R.lower && L.upper == R.upper;
                }

                case And::  UUID:
                case Or::   UUID:
                case None:: UUID:
                    return Logic::HaveSamePatterns( dynamic_cast<const Logic&>(lhs), dynamic_cast<const Logic&>(rhs) );


                case Optional::UUID:
                    return Joker::HaveSameMotif(dynamic_cast<const Joker &>(lhs),dynamic_cast<const Joker &>(rhs));

                case Repeating:: UUID: {
                    const Repeating &L = dynamic_cast<const Repeating &>(lhs);
                    const Repeating &R = dynamic_cast<const Repeating &>(rhs);
                    return L.atLeast == R.atLeast && Joker::HaveSameMotif(L,R);
                }

                case Counting:: UUID: {
                    const Counting &L = dynamic_cast<const Counting &>(lhs);
                    const Counting &R = dynamic_cast<const Counting &>(rhs);
                    return L.lower == R.lower && L.upper == R.upper && Joker::HaveSameMotif(L,R);
                }
                    

                default:
                    std::cerr << "[unhandled " << FourCC(uid).c_str() << " comparison]" << std::endl;
                    break;
            }

            return false;
        }
    }

}


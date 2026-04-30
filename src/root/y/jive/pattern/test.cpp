
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
                case Any1::     UUID: return true;
                case Single::   UUID: return dynamic_cast<const Single   &>(lhs).code == dynamic_cast<const Single   &>(rhs).code;
                case Excluded:: UUID: return dynamic_cast<const Excluded &>(lhs).code == dynamic_cast<const Excluded &>(rhs).code;
                case Range:: UUID: {
                    const Range &L = dynamic_cast<const Range&>(lhs);
                    const Range &R = dynamic_cast<const Range&>(rhs);
                    return L.lower == R.lower && L.upper == R.upper;
                }

                case And::UUID:
                case Or::UUID:
                    return Logic::HaveSamePatterns( dynamic_cast<const Logic&>(lhs), dynamic_cast<const Logic&>(rhs) );

                default:
                    std::cerr << "[unhandled " << FourCC(uid).c_str() << "]" << std::endl;
                    break;
            }

            return false;
        }
    }

}


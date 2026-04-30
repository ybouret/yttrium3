#include "y/apex/rational.hpp"


namespace Yttrium
{
    namespace Apex
    {
        size_t Rational:: serialize(OutputStream &fp) const
        {
            const size_t res = numer.serialize(fp);
            return res + denom.serialize(fp);

        }

        Rational Rational:: Read(InputStream &fp, const char * const varName)
        {
            const apz nn = apz::Read(fp,varName);
            const apn dd = apn::Read(fp,varName);
            if(dd.is0())
            {
                Specific::Exception excp(CallSign,"corrupted read");
                throw excp.signedFor(varName, "denominator");
            }
            const Rational q(nn,dd);
            if(q.denom!=dd)
            {
                Specific::Exception excp(CallSign,"not reduced");
                throw excp.signedFor(varName, "reprentation");
            }
            return q;
        }
    }

}

#include "y/jive/pattern/all.hpp"
#include "y/stream/input.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        static inline
        Pattern * LoadLogic(Logic * const p, InputStream &fp)
        {
            AutoPtr<Logic> q(p);
            q->load(fp);
            return q.yield();
        }

        Pattern * Pattern:: Load(InputStream &fp)
        {

            const uint32_t     uid = fp.cbr<uint32_t>("Pattern","UUID");
            const FourCC       fcc(uid);
            const char * const varName = fcc.c_str();

            switch(uid)
            {
                case Any1::     UUID: return new Any1();
                case Single::   UUID: return new Single( fp.cbr<uint8_t>(varName,"code") );
                case Excluded:: UUID: return new Excluded( fp.cbr<uint8_t>(varName,"code") );
                case Range::    UUID:
                {
                    const uint8_t lower = fp.cbr<uint8_t>(varName,"lower");
                    const uint8_t upper = fp.cbr<uint8_t>(varName,"upper");
                    if(upper<lower) throw Specific::Exception(varName,"corrupted lower/upper");
                    return new Range(lower,upper);
                }

                case And:: UUID:  return LoadLogic( new And(), fp );
                case Or::  UUID:  return LoadLogic( new Or(), fp );

            }

            throw Specific::Exception(varName, "unknown UUID was read");
        }
    }

}

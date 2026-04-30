
#include "y/apex/n/code.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Apex
    {
        size_t Natural:: serialize(OutputStream &fp) const
        {
            assert(code);
            const KegType &keg = *static_cast<const KegType *>(code);
            const size_t   num = keg.bytes;
            size_t res = fp.vbr(num);
            for(size_t i=0;i<num;++i)
            {
                const uint8_t b = keg.getByte(i);
                res += fp.cbr(b);
            }
            return res;
        }

        Natural Natural:: Read(InputStream &fp, const char * const varName)
        {
            const size_t num = fp.vbr<size_t>(varName,"bytes");
            if(num<=0) return Natural();
            AutoPtr<KegType> keg = new KegType(num);
            Coerce(keg->words)   = Alignment::To<_Keg::Word>::Ceil(num)/sizeof(_Keg::Word);

            for(size_t i=0;i<num;++i)
            {
                const _Keg::Word b = fp.cbr<uint8_t>(varName,"byte");
                _Keg::Word &     w = keg->word[i/sizeof(_Keg::Word)];
                w |= ( b << ((i%sizeof(_Keg::Word))<<3) );
            }
            keg->update();
            if(keg->bytes!=num)
            {
                Specific::Exception excp(CallSign,"Read corrupted");
                throw excp.signedFor(varName,"content");
            }
            return Natural(Directly,keg.yield());
        }
    }

}

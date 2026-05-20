
#include "y/information/bwt/transformer.hpp"
#include "y/type/destroy.hpp"
#include "y/object.hpp"
#include "y/memory/troop/legacy.hpp"
#include "y/core/max.hpp"
#include "y/information/bwt/bwt.hpp"

namespace Yttrium
{
    namespace Information
    {

        typedef Memory::LegacyTroop<size_t,Object> BWT_CodeType;

        class BWT_Transformer :: Code : public BWT_CodeType
        {
        public:
            
            inline explicit Code(const size_t n) :
            BWT_CodeType(Max<size_t>(n,8))
            {
                assert(size>=n);
            }

            inline virtual ~Code() noexcept
            {
            }


        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        BWT_Transformer:: BWT_Transformer() noexcept :
        code(0)
        {
        }

        BWT_Transformer:: ~BWT_Transformer() noexcept
        {
            if(code)
                Destroy(code);
        }


        void BWT_Transformer:: make(const size_t length)
        {
            if(0==code)
            {
                code = new Code(length);
            }
            else
            {
                if(code->size<length)
                {
                    Destroy(code);
                    code = new Code(length);

                }
            }

            assert(0!=code);
            assert(code->size>=length);
        }

        size_t BWT_Transformer:: encode(void * const       target,
                                        const void * const source,
                                        const size_t       length)
        {
            assert( !(0==target&&length>0) );
            assert( !(0==source&&length>0) );
            make(length);
            return BWT::Encode(target, source, length, code->addr);
        }

        void   BWT_Transformer:: decode(void * const       target,
                                        const void * const source,
                                        const size_t       length,
                                        const size_t       primary)
        {
            assert( !(0==target&&length>0) );
            assert( !(0==source&&length>0) );
            make(length);
            BWT::Decode(target,source,length,code->addr,primary);
        }

    }

}


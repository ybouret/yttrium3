
#include "y/mkl/tao/device.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Tao
        {

            class Device:: Code :
            public Object
            {
            public:
                inline explicit Code(const size_t ncpu,
                                     Lockable    &sync) :
                scheme(ncpu),
                tiles1d(scheme,sync),
                tiles2d(scheme,sync),
                udts(scheme,sync)
                {
                    
                }


                inline virtual ~Code() noexcept {}

                Concurrent::Splitting::Scheme scheme;
                Tiles1D                       tiles1d;
                Tiles2D                       tiles2d;
                UDTS                          udts;

            private:
                Y_Disable_Copy_And_Assign(Code);
            };


            Device:: ~Device() noexcept
            {
                assert(code);
                Destroy(code);
            }

            Device:: Device(const Concurrent::Engine &engine) :
            Concurrent::Engine(engine),
            code( new Code(simd->size(),simd->sync() ) ),
            localCache( *code->scheme.localMemory )
            {
            }

            size_t Device:: SizeOfCode() noexcept
            {
                return sizeof(Code);
            }

        }


    }
}

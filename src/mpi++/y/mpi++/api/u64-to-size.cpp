#include "y/mpi++/api.hpp"
namespace Yttrium
{
    namespace
    {
        template <bool>
        struct U64ToSize;

        template <>
        struct U64ToSize<false>
        {
            static inline size_t Convert(const uint64_t u64)
            {
                static const uint64_t MaxSize = IntegerFor<size_t>::Maximum;
                assert(sizeof(size_t)<sizeof(uint64_t));
                if(u64>MaxSize) throw Specific::Exception(MPI::CallSign,"received size overflow");
                return (size_t)u64;
            }
        };


        template <>
        struct U64ToSize<true>
        {
            static inline size_t Convert(const uint64_t u64) noexcept
            {
                assert(sizeof(size_t)>=sizeof(uint64_t));
                return u64;
            }
        };



    }
    
    size_t MPI:: ConvertU64ToSize(const uint64_t u64)
    {
        return U64ToSize< sizeof(size_t)>=sizeof(uint64_t) >::Convert(u64);
    }

}

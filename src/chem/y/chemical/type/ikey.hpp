
//! \file

#ifndef Y_Chemical_IKey_Included
#define Y_Chemical_IKey_Included 1

#include "y/container/cxx/array.hpp"
#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class IKey : public Memory::ReadOnlyBuffer, public CxxArray<const size_t>
        {
        public:
            template <typename READABLE> inline
            explicit IKey(READABLE &arr) :
            Memory::ReadOnlyBuffer(),
            CxxArray<const size_t>(CopyOf,arr),
            bytes( size() * sizeof(size_t) )
            {
                assert(bytes>0);
            }

            virtual ~IKey() noexcept;

            virtual size_t       length() const noexcept;
            virtual const void * ro()     const noexcept;
            

        private:
            Y_Disable_Assign(IKey);
            const size_t bytes;
        };


    }

}

#endif // !Y_Chemical_IKey_Included


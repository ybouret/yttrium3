
//! \file

#ifndef Y_Associative_AddrKey_Inluded
#define Y_Associative_AddrKey_Inluded 1

#include "y/type/args.hpp"
#include "y/type/ints.hpp"
#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{
    class AddrKey : public Memory::ReadOnlyBuffer
    {
    public:
        static const size_t Length = sizeof(void*);
        typedef UnsignedFor<Length>::Alias::Type UType;

        template <typename T> inline
        explicit AddrKey(T &ref) noexcept :
        data()
        {
            fillWith( &ref );
        }
        AddrKey(const AddrKey &) noexcept;
        virtual ~AddrKey() noexcept;
        Y_OSTREAM_PROTO(AddrKey);
        
        virtual const void * ro()     const noexcept;
        virtual size_t       length() const noexcept;

    private:
        Y_Disable_Assign(AddrKey);
        void fillWith(const void * const addr) noexcept;
        uint8_t data[Length];
    };

}

#endif // !Y_Associative_AddrKey_Inluded

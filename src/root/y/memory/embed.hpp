
//! \file

#ifndef Y_Memory_Embedded_Included
#define Y_Memory_Embedded_Included 1


#include "y/config/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Embed
        {
        public:

            static size_t Format(Embed [], const size_t)              noexcept;
            static void   Assign(void * const, Embed[], const size_t) noexcept;

            template <typename T> inline explicit
            Embed(T * & entry, const size_t count) noexcept :
            pblock( (void**) &entry ),
            length( count * sizeof(T) ),
            offset(0)
            {

            }

            Embed(const Embed &) noexcept;
            ~Embed() noexcept;
            Y_OSTREAM_PROTO(Embed);

            size_t nextOffset() const noexcept;
            void   assignFrom(void * const) noexcept;
            
            void **      pblock;
            const size_t length;
            size_t       offset;

        private:
            Y_Disable_Assign(Embed);
        };



    }

}

#endif // !Y_Memory_Embedded_Included

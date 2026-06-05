
//! file

#ifndef Y_Field_Included
#define Y_Field_Included 1

#include "y/string.hpp"

namespace Yttrium
{
    namespace Field
    {
        class Field
        {
        public:
            template <typename ID> inline
            explicit Field(const ID &id) : name(id)
            {
            }

            virtual ~Field() noexcept;



            const String name;

            static void *AcquireMemory(size_t &bytes);
            static void  ReleaseMemory(void * &entry, size_t &bytes) noexcept;
            String       subFieldId(const unit_t) const;

        private:
            Y_Disable_Copy_And_Assign(Field);
        };
    }

}

#endif // !Y_Field_Included


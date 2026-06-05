
#include "y/field/field.hpp"
#include "y/object/factory.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Field
    {
        Field:: ~Field() noexcept
        {
        }

        void * Field:: AcquireMemory(size_t &bytes)
        {
            static Memory::Allocator &mgr = Object::Factory::Instance();
            assert(bytes>0);
            std::cerr << "acquire " << bytes << std::endl;
            return mgr.acquire(bytes);
        }

        void Field:: ReleaseMemory(void *&entry, size_t &bytes) noexcept
        {
            static Memory::Allocator &mgr = Object::Factory::Instance();
            assert(bytes>0);
            assert(0!=entry);
            std::cerr << "release " << bytes << std::endl;
            return mgr.release(entry,bytes);
        }

        String Field:: subFieldId(const unit_t u) const
        {
            return name + '[' + Decimal(u).c_str() + ']';
        }

    }

}


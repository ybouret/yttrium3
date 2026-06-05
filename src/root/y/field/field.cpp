
#include "y/field/field.hpp"
#include "y/object/factory.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Field
    {
        CoreField:: ~CoreField() noexcept
        {
        }

        void * CoreField:: AcquireMemory(size_t &bytes)
        {
            static Memory::Allocator &mgr = Object::Factory::Instance();
            assert(bytes>0);
            std::cerr << "acquire " << bytes << std::endl;
            return mgr.acquire(bytes);
        }

        void CoreField:: ReleaseMemory(void *&entry, size_t &bytes) noexcept
        {
            static Memory::Allocator &mgr = Object::Factory::Instance();
            assert(bytes>0);
            assert(0!=entry);
            std::cerr << "release " << bytes << std::endl;
            return mgr.release(entry,bytes);
        }

        String CoreField:: subFieldId(const unit_t u) const
        {
            return name + '[' + Decimal(u).c_str() + ']';
        }

    }

}


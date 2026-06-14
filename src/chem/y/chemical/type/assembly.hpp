
//! \file

#ifndef Y_Chemical_Assembly_Included
#define Y_Chemical_Assembly_Included 1

#include "y/chemical/type/entity.hpp"
#include "y/format/justify.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Assembly
        {
        public:
            explicit Assembly() noexcept;
            virtual ~Assembly() noexcept;
            Assembly(const Assembly &) noexcept;
            
            void enroll(const Entity &) noexcept;

            std::ostream & print(std::ostream &os, const Entity &, const Justify::Type = Justify::Left) const;


            const size_t width;
        private:
            Y_Disable_Assign(Assembly);

        };
    }

}

#endif // !Y_Chemical_Assembly_Included

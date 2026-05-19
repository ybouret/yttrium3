
//! \file

#ifndef Y_Cameo_Addition_Included
#define Y_Cameo_Addition_Included 1


#include "y/cameo/sum/operating.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        template <typename T>
        class Addition : public Sum::Operating<T>::Type
        {
        public:
            typedef typename  Sum::Operating<T>::Type SummatorType;
            static const bool IsSummator = Y_Is_SuperSubClass_Strict(Summator<T>,Addition);

            inline explicit Addition() : SummatorType() {}
            inline explicit Addition(const size_t minCapacity) : SummatorType(minCapacity) {}
            inline virtual ~Addition() noexcept {}
            inline Addition(const Addition &other) : SummatorType(other) {}
            
        private:
            Y_Disable_Assign(Addition);
        };
    }
}

#endif // !Y_Cameo_Addition_Included




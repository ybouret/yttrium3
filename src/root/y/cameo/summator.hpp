//! \file

#ifndef Y_Cameo_Summator_Included
#define Y_Cameo_Summator_Included 1

#include "y/container.hpp"
#include "y/type/args.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        template <typename T>
        class Summator
        {
        public:
            Y_Args_Declare(T,Type);

            inline explicit Summator() noexcept {}
            inline virtual ~Summator() noexcept {}

            virtual void ldz() noexcept   = 0;
            virtual void add(ConstType &) = 0;
            virtual Type operator()(void) = 0;

            inline Summator & operator<<(ParamType data) {
                add(data); return *this;
            }

            inline Summator operator +=(ParamType data) {
                add(data); return *this;
            }

            inline Summator & operator=(ParamType data) {
                ldz(); add(data); return *this;
            }

        private:
            Y_Disable_Copy_And_Assign(Summator);
        };

    }

}

#endif // !Y_Cameo_Summator_Included


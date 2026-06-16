
#ifndef Y_Chemical_Conservation_Law_Included
#define Y_Chemical_Conservation_Law_Included 1

#include "y/chemical/reactive/actors.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

            class Law : public Actors
            {
            public:
                typedef CxxListOf<Law> List;
                
                explicit Law() noexcept;
                virtual ~Law() noexcept;
                Y_OSTREAM_PROTO(Law);

                xreal_t excess(const XReadable &, const Level, XAdd &) const;

                Law * next;
                Law * prev;
            private:
                Y_Disable_Copy_And_Assign(Law);
            };

        }
    }

}

#endif // !Y_Chemical_Conservation_Law_Included


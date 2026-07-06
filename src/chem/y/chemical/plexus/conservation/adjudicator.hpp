
#ifndef Y_Chemical_Conservation_Adjudicator_Included
#define Y_Chemical_Conservation_Adjudicator_Included 1

#include "y/chemical/plexus/conservation/canon.hpp"
#include "y/chemical/plexus/conservation/law/broken.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

         

            class Adjudicator : public Object
            {
            public:

                explicit Adjudicator(const Canon &);
                virtual ~Adjudicator() noexcept;

                const Canon    & canon;
                BList            blist;
                XAdd             xadd;
                const size_t     n;       //!< number of laws
                const size_t     m;       //!< number of species
                XMatrix          wksp;    //!< workspace

                void judge(XML::Log &xml, XWritable &C, const Level L);

            private:
                Y_Disable_Copy_And_Assign(Adjudicator);
                
            };

        }

    }

}

#endif // !Y_Chemical_Conservation_Adjudicator_Included



#include "y/concurrent/thread/venue.hpp"
#include "y/system/hardware.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        VenueList:: VenueList() noexcept : CountedObject(), VList() {}

        VenueList:: ~VenueList() noexcept
        {
        }

        Venue:: Venue(const size_t ncpu) : SharedVList( new VenueList() )
        {
            const size_t n = ncpu <= 0 ? Hardware::NumProcs() : ncpu;
            for(size_t i=0;i<n;++i)
                **this << i;
        }

        Venue:: Venue(const Venue &v) noexcept : SharedVList(v)
        {
        }

        Venue:: ~Venue() noexcept
        {
        }
        

    }

}

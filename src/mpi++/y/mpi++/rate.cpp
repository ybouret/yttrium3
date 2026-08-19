#include "y/mpi++/api.hpp"

namespace Yttrium
{
    MPI:: Rate:: Rate() noexcept : bytes(0), ticks(0)
    {
    }

    MPI::Rate:: ~Rate() noexcept
    {

    }

    MPI:: Rate:: Rate(const Rate &_) noexcept : bytes(_.bytes), ticks(_.ticks)
    {
    }

    HumanReadable MPI:: Rate:: hrt( const System::WallTime &chrono ) const
    {
        if(ticks<=0)
        {
            return HumanReadable(0);
        }
        else
        {
            const long double speed = (long double) bytes / chrono(ticks);
            return HumanReadable( (uint64_t)speed );
        }
    }

    void MPI:: Rate:: ldz() noexcept
    {
        ticks = 0;
        bytes = 0;
    }

    String MPI:: Rate:: str( const System::WallTime &chrono ) const
    {
        const HumanReadable total(bytes);
        const HumanReadable speed = hrt(chrono);
        return total.str() + 'B' + ' ' + '@' + speed.str() + 'B' + '/' + 's';
    }

}


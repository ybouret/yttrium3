

#ifndef Y_MPI_Codec_Included
#define Y_MPI_Codec_Included 1

#include "y/mpi++/api.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! MPI Codec for a given type
    //
    //
    //__________________________________________________________________________
    class MPI:: Codec
    {
    public:

        int LegacyScalar;
        int LegacyVector;
        int SerializedIO;
        

        virtual ~Codec() noexcept; //!< cleanup

    private:
        Y_Disable_Copy_And_Assign(Codec); //!< discard
    };

}

#endif // !Y_MPI_Codec_Included

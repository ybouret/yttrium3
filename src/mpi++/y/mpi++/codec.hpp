

#ifndef Y_MPI_Codec_Included
#define Y_MPI_Codec_Included 1

#include "y/mpi++/api.hpp"

namespace Yttrium
{

    class MPI:: Codec
    {
    public:

        virtual ~Codec() noexcept;

    private:
        Y_Disable_Copy_And_Assign(Codec);
    };

}

#endif // !Y_MPI_Codec_Included

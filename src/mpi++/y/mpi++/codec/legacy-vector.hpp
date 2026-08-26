

#ifndef Y_MPI_Codec_Legacy_Vector_Included
#define Y_MPI_Codec_Legacy_Vector_Included 1

#include "y/mpi++/codec.hpp"

namespace Yttrium
{

    class MPI:: LegacyVectorCodec : public Codec
    {
    public:
        explicit LegacyVectorCodec(const MPI            & mpi,
                                   const std::type_info & tid,
                                   const size_t           dim);
        virtual ~LegacyVectorCodec() noexcept;

        const DataType dataType;
        const size_t   dimensions;

    private:
        Y_Disable_Copy_And_Assign(LegacyVectorCodec);
    };

}

#endif // !Y_MPI_Codec_Legacy_Vector_Included


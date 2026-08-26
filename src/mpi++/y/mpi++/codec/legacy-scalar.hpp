
#ifndef Y_MPI_Codec_Legacy_Scalar_Included
#define Y_MPI_Codec_Legacy_Scalar_Included 1

#include "y/mpi++/codec.hpp"

namespace Yttrium
{

    class MPI:: LegacyScalarCodec : public Codec
    {
    public:
        explicit LegacyScalarCodec(const MPI &, const std::type_info &);
        virtual ~LegacyScalarCodec() noexcept;

        virtual void send(MPI &              mpi,
                          const void * const blockAddr,
                          const size_t       numBlocks,
                          const size_t       dest,
                          const int          tag);

        const DataType dataType;

    private:
        Y_Disable_Copy_And_Assign(LegacyScalarCodec);
    };

}

#endif // !Y_MPI_Codec_Legacy_Scalar_Included


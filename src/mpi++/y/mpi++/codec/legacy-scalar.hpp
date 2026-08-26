
#ifndef Y_MPI_Codec_Legacy_Scalar_Included
#define Y_MPI_Codec_Legacy_Scalar_Included 1

#include "y/mpi++/codec.hpp"

namespace Yttrium
{

    class MPI:: LegacyScalarCodec : public Codec
    {
    public:
        explicit LegacyScalarCodec(const std::type_info &);
        virtual ~LegacyScalarCodec() noexcept;
        
    private:
        Y_Disable_Copy_And_Assign(LegacyScalarCodec);
    };

}

#endif // !Y_MPI_Codec_Legacy_Scalar_Included


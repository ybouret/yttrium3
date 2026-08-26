

#ifndef Y_MPI_Codec_SerializedIO_Included
#define Y_MPI_Codec_SerializedIO_Included 1

#include "y/mpi++/codec.hpp"
#include "y/stream/memory/output.hpp"

namespace Yttrium
{

    class MPI:: SerializedIOCodec : public Codec
    {
    public:
        explicit SerializedIOCodec(const MPI &, const std::type_info &);
        virtual ~SerializedIOCodec() noexcept;

        OutputMemoryStream buffer;
        
    private:
        Y_Disable_Copy_And_Assign(SerializedIOCodec);
    };

}

#endif // !Y_MPI_Codec_SerializedIO_Included


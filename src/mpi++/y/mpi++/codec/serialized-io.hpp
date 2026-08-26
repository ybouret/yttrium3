

#ifndef Y_MPI_Codec_SerializedIO_Included
#define Y_MPI_Codec_SerializedIO_Included 1

#include "y/mpi++/codec.hpp"
#include "y/stream/memory/output.hpp"

namespace Yttrium
{

    class MPI:: SerializedIOCodec : public Codec
    {
    public:
        explicit SerializedIOCodec(const std::type_info &);
        virtual ~SerializedIOCodec() noexcept;

        OutputMemoryStream buffer;
        
    private:
        Y_Disable_Copy_And_Assign(SerializedIOCodec);
    };

    template <typename T>
    class MPI_Serializer : public MPI::SerializedIOCodec
    {
    public:
        inline explicit MPI_Serializer() : MPI::SerializedIOCodec( typeid(T) )
        {
        }

        inline virtual ~MPI_Serializer() noexcept {}

        virtual void send(MPI &              mpi,
                          const void * const blockAddr,
                          const size_t       numBlocks,
                          const size_t       dest,
                          const int          tag)
        {
            // collect objects
            size_t written = 0;
            buffer->free();
            {
                const T * p = static_cast<const T *>(blockAddr);
                for(size_t i=numBlocks;i>0;--i,++p)
                {
                    written += p->serialize(buffer);
                }
                assert(buffer->size() == written);
            }

            // send size
            mpi.sendSize(written,dest,tag);

            // send data
            mpi.sendBytes(buffer.data(),written,dest,tag);
        }

    private:
        Y_Disable_Copy_And_Assign(MPI_Serializer);
    };

}

#endif // !Y_MPI_Codec_SerializedIO_Included


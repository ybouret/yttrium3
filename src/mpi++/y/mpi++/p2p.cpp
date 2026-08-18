
#include "y/mpi++/api.hpp"

namespace Yttrium
{

    void MPI::send(const void * const buffer,
                   const size_t       count,
                   const MPI_Datatype datatype,
                   const uint64_t     bytes,
                   const size_t       dest,
                   const int          tag,
                   const MPI_Comm     comm)
    {
        assert(dest<size);
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Send(buffer, GetCount(count,"MPI_Send"),datatype,(int)dest,tag,comm));
        sendRate.ticks += Y_MPI_Gain();
        sendRate.bytes += bytes;
    }

    void MPI:: recv(void *const        buffer,
                    const size_t       count,
                    const MPI_Datatype datatype,
                    const uint64_t     bytes,
                    const size_t       source,
                    const int          tag,
                    const MPI_Comm     comm)
    {
        assert(source<size);
        MPI_Status st;
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Recv(buffer,GetCount(count,"MPI_Recv"),datatype,(int)source,tag,comm,&st));
        recvRate.ticks += Y_MPI_Gain();
        recvRate.bytes += bytes;
    }

    namespace
    {
        static const char SYMB = 'Y';
    }

    void MPI:: syn(const size_t source)
    {
        char c = 0;
        recv(&c,1,MPI_CHAR,1,source);
        if(SYMB!=c) throw Specific::Exception("MPI::syn","corrupted I/O");
    }

    void MPI:: ack(const size_t target)
    {
        send(&SYMB,1,MPI_CHAR,1,target);
    }

    void MPI:: syncWith(const size_t target)
    {
        ack(target);
        syn(target);
    }

    void MPI:: sendBytes(const void * const buffer,
                         const size_t       length,
                         const size_t       dest,
                         const int          tag,
                         const MPI_Comm     comm)
    {
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Send(buffer, GetCount(length,"MPI::sendBytes"),MPI_BYTE,(int)dest,tag,comm));
        sendRate.ticks += Y_MPI_Gain();
        sendRate.bytes += length;
    }

    void MPI:: recvBytes(void * const   buffer,
                         size_t         length,
                         const size_t   src,
                         const int      tag,
                         const MPI_Comm comm)
    {
        MPI_Status st;
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Recv(buffer,GetCount(length,"MPI::recvBytes"),MPI_BYTE,(int)src,tag,comm,&st));
        recvRate.ticks += Y_MPI_Gain();
        recvRate.bytes += length;
    }

}

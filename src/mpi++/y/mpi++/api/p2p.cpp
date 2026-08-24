
#include "y/mpi++/api.hpp"

namespace Yttrium
{

    void MPI::send(const void * const buffer,
                   const size_t       count,
                   const MPI_Datatype datatype,
                   const uint64_t     bytes,
                   const size_t       dest,
                   const int          tag)
    {
        assert(dest<size);
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Send(buffer, GetCount(count,"MPI_Send"),datatype,(int)dest,tag,MPI_COMM_WORLD));
        sendRate.ticks += Y_MPI_Gain();
        sendRate.bytes += bytes;
    }

    void MPI:: recv(void *const        buffer,
                    const size_t       count,
                    const MPI_Datatype datatype,
                    const uint64_t     bytes,
                    const size_t       source,
                    const int          tag)
    {
        assert(source<size);
        MPI_Status st;
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Recv(buffer,GetCount(count,"MPI_Recv"),datatype,(int)source,tag,MPI_COMM_WORLD,&st));
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
                         const int          tag)
    {
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Send(buffer, GetCount(length,"MPI::sendBytes"),MPI_BYTE,(int)dest,tag,MPI_COMM_WORLD));
        sendRate.ticks += Y_MPI_Gain();
        sendRate.bytes += length;
    }

    void MPI:: recvBytes(void * const   buffer,
                         const size_t   length,
                         const size_t   src,
                         const int      tag)
    {
        MPI_Status st;
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Recv(buffer,GetCount(length,"MPI::recvBytes"),MPI_BYTE,(int)src,tag,MPI_COMM_WORLD,&st));
        recvRate.ticks += Y_MPI_Gain();
        recvRate.bytes += length;
    }

    void MPI:: sendSize(const size_t       length,
                        const size_t       dest,
                        const int          tag)
    {
        const uint64_t u64 = length;
        send1(u64,dest,tag);
    }


    size_t MPI:: recvSize(const size_t   src,
                          const int      tag)
    {
        return ConvertU64ToSize( recv1<uint64_t>(src,tag) );
    }


    void MPI:: sendrecv(const void * const sendbuf,
                        const size_t       sendcount,
                        const MPI_Datatype sendtype,
                        const uint64_t     sendbytes,
                        const size_t       dest,
                        void * const       recvbuf,
                        const size_t       recvcount,
                        const MPI_Datatype recvtype,
                        const uint64_t     recvbytes,
                        const size_t       source,
                        const int          sendtag,
                        const int          recvtag)
    {
        static const char fn[] = "MPI_Sendrecv";
        MPI_Status        st;

        Y_MPI_Mark();
        Y_MPI_Call(MPI_Sendrecv(sendbuf, GetCount(sendcount,fn),sendtype, (int)dest, sendtag,
                                recvbuf, GetCount(recvcount,fn),recvtype, (int)source,recvtag,
                                MPI_COMM_WORLD,&st));
        const uint64_t ell = Y_MPI_Gain();
        recvRate.ticks += ell;
        recvRate.bytes += recvbytes;

        sendRate.ticks += ell;
        sendRate.bytes += sendbytes;

    }


    size_t MPI:: sendRecvSize(const size_t sendLength,
                              const size_t sendRank,
                              const size_t recvRank,
                              const int    sendtag,
                              const int    recvtag)
    {
        static const DataType &_ = getDataTypeOf<uint64_t>();
        const uint64_t s64 = sendLength;
        uint64_t       r64 = 0;
        sendrecv(&s64,1,_.dt,sizeof(uint64_t),sendRank,
                 &r64,1,_.dt,sizeof(uint64_t),recvRank,
                 sendtag,
                 recvtag);
        return ConvertU64ToSize(r64);
    }


    void MPI:: sendrecvBytes(const void * const sendbuf,
                             const size_t       sendcount,
                             const size_t       dest,
                             void * const       recvbuf,
                             const size_t       recvcount,
                             const size_t       source,
                             const int          sendtag,
                             const int          recvtag)
    {
        sendrecv(sendbuf,sendcount,MPI_BYTE,sendcount,dest,
                 recvbuf,recvcount,MPI_BYTE,recvcount,source,
                 sendtag,recvtag);
    }


}


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
                         const size_t   length,
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

    void MPI:: sendSize(const size_t       length,
                        const size_t       dest,
                        const int          tag ,
                        const MPI_Comm     comm)
    {
        const uint64_t u64 = length;
        send1(u64,dest,tag,comm);
    }

    namespace
    {
        template <bool>
        struct U64ToSize;

        template <>
        struct U64ToSize<false>
        {
            static inline size_t Convert(const uint64_t u64)
            {
                static const uint64_t MaxSize = IntegerFor<size_t>::Maximum;
                assert(sizeof(size_t)<sizeof(uint64_t));
                if(u64>MaxSize) throw Specific::Exception(MPI::CallSign,"MPI::recvSize overflow");
                return (size_t)u64;
            }
        };


        template <>
        struct U64ToSize<true>
        {
            static inline size_t Convert(const uint64_t u64) noexcept
            {
                assert(sizeof(size_t)>=sizeof(uint64_t));
                return u64;
            }
        };

    }

    size_t MPI:: recvSize(const size_t   src,
                          const int      tag  ,
                          const MPI_Comm comm)
    {
        const uint64_t        u64 = recv1<uint64_t>(src,tag,comm);
        return U64ToSize<sizeof(size_t)>=sizeof(uint64_t)>::Convert(u64);
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
                        const int          recvtag,
                        const MPI_Comm     comm )
    {
        static const char fn[] = "MPI_Sendrecv";
        MPI_Status        st;

        Y_MPI_Mark();
        Y_MPI_Call(MPI_Sendrecv(sendbuf, GetCount(sendcount,fn),sendtype, (int)dest, sendtag,
                                recvbuf, GetCount(recvcount,fn),recvtype, (int)source,recvtag,
                                comm,&st));
        const uint64_t ell = Y_MPI_Gain();
        recvRate.ticks += ell;
        recvRate.bytes += recvbytes;

        sendRate.ticks += ell;
        sendRate.bytes += sendbytes;

    }

    void MPI:: sendrecvBytes(const void * const sendbuf,
                             const size_t       sendcount,
                             const size_t       dest,
                             void * const       recvbuf,
                             const size_t       recvcount,
                             const size_t       source,
                             const int          sendtag,
                             const int          recvtag,
                             const MPI_Comm     comm)
    {
        sendrecv(sendbuf,sendcount,MPI_BYTE,sendcount,dest,
                 recvbuf,recvcount,MPI_BYTE,recvcount,source,
                 sendtag,recvtag,comm);
    }


}

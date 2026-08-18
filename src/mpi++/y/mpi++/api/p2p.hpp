
void send(const void * const buffer,
          const size_t       count,
          const MPI_Datatype datatype,
          const uint64_t     bytes,
          const size_t       dest,
          const int          tag = DefaultTag,
          const MPI_Comm     comm = MPI_COMM_WORLD);


void recv(void * const       buffer,
          const size_t       count,
          const MPI_Datatype datatype,
          const uint64_t     bytes,
          const size_t       src,
          const int          tag = DefaultTag,
          const MPI_Comm     comm = MPI_COMM_WORLD);

void sendrecv(const void * const sendbuf,
              const size_t       sendcount,
              const MPI_Datatype sendtype,
              const uint64_t     sendbytes,
              const size_t       dest,
              void * const       recvbuf,
              const size_t       recvcount,
              const MPI_Datatype recvtype,
              const uint64_t     recvbytes,
              const size_t       source,
              const int          sendtag = DefaultTag,
              const int          recvtag = DefaultTag,
              const MPI_Comm     comm = MPI_COMM_WORLD);


void sendSize(const size_t       length,
              const size_t       dest,
              const int          tag  = DefaultTag,
              const MPI_Comm     comm = MPI_COMM_WORLD);

size_t recvSize(const size_t   src,
                const int      tag  = DefaultTag,
                const MPI_Comm comm = MPI_COMM_WORLD);

void sendBytes(const void * const buffer,
               const size_t       length,
               const size_t       dest,
               const int          tag  = DefaultTag,
               const MPI_Comm     comm = MPI_COMM_WORLD);

void recvBytes(void * const   buffer,
               size_t         length,
               const size_t   src,
               const int      tag  = DefaultTag,
               const MPI_Comm comm = MPI_COMM_WORLD);


void sendrecvBytes(const void * const sendbuf,
                   const size_t       sendcount,
                   const size_t       dest,
                   void * const       recvbuf,
                   const size_t       recvcount,
                   const size_t       source,
                   const int          sendtag = DefaultTag,
                   const int          recvtag = DefaultTag,
                   const MPI_Comm     comm = MPI_COMM_WORLD);

template <typename T> inline
void send1(const T      & obj,
           const size_t   dst,
           const int      tag  = DefaultTag,
           const MPI_Comm comm = MPI_COMM_WORLD)
{
    static const DataType _ = getDataTypeOf<T>();
    send( &obj, 1, _.dt, sizeof(T), dst, tag, comm);
}


template <typename T> inline
T recv1(const size_t   src,
        const int      tag  = DefaultTag,
        const MPI_Comm comm = MPI_COMM_WORLD)
{
    static const DataType _ = getDataTypeOf<T>();
    Memory::Moniker<T> moniker;
    T * const          addr = & *moniker;
    recv(addr,1,_.dt,sizeof(T),src,tag,comm);
    return *addr;
}



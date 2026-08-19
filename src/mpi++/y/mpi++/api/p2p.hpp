
void send(const void * const buffer,
          const size_t       count,
          const MPI_Datatype datatype,
          const uint64_t     bytes,
          const size_t       dest,
          const int          tag = DefaultTag);


void recv(void * const       buffer,
          const size_t       count,
          const MPI_Datatype datatype,
          const uint64_t     bytes,
          const size_t       src,
          const int          tag = DefaultTag);

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
              const int          recvtag = DefaultTag);


void sendSize(const size_t       length,
              const size_t       dest,
              const int          tag  = DefaultTag);

size_t recvSize(const size_t   src,
                const int      tag  = DefaultTag);

void sendBytes(const void * const buffer,
               const size_t       length,
               const size_t       dest,
               const int          tag  = DefaultTag);

void recvBytes(void * const   buffer,
               size_t         length,
               const size_t   src,
               const int      tag  = DefaultTag);


void sendrecvBytes(const void * const sendbuf,
                   const size_t       sendcount,
                   const size_t       dest,
                   void * const       recvbuf,
                   const size_t       recvcount,
                   const size_t       source,
                   const int          sendtag = DefaultTag,
                   const int          recvtag = DefaultTag);

template <typename T> inline
void send1(const T      & obj,
           const size_t   dst,
           const int      tag  = DefaultTag)
{
    static const DataType _ = getDataTypeOf<T>();
    send( &obj, 1, _.dt, sizeof(T), dst, tag);
}


template <typename T> inline
T recv1(const size_t   src,
        const int      tag  = DefaultTag)
{
    static const DataType _ = getDataTypeOf<T>();
    Memory::Moniker<T> moniker;
    T * const          addr = & *moniker;
    recv(addr,1,_.dt,sizeof(T),src,tag);
    return *addr;
}



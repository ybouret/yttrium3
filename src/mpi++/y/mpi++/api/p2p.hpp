//! MPI_Send
/**
 \param buffer   source buffer
 \param count    count of objects
 \param datatype datatype to send
 \param bytes    buffer size
 \param dest     rank destination
 \param tag      optional tag
 */
void send(const void * const buffer,
          const size_t       count,
          const MPI_Datatype datatype,
          const uint64_t     bytes,
          const size_t       dest,
          const int          tag = DefaultTag);


//! MPI_Recv
/**
 \param buffer   target buffer
 \param count    count of objects
 \param datatype datatype to send
 \param bytes    buffer size
 \param src      rank source
 \param tag      optional tag
 */
void recv(void * const       buffer,
          const size_t       count,
          const MPI_Datatype datatype,
          const uint64_t     bytes,
          const size_t       src,
          const int          tag = DefaultTag);

//! MPI_Sendrecv
/**
 \param sendbuf   send buffer
 \param sendcount count of objects to send
 \param sendtype  type of objects to send
 \param sendbytes length of sendbuf
 \param dest      destination rank
 \param recvbuf   recv buffer
 \param recvcount count of objects to receive
 \param recvtype  type of objects to receive
 \param recvbytes length of recvbuf
 \param source    source rank
 \param sendtag   optional tag
 \param recvtag   optional tag
 */
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

//! MPI_Send size_t
/**
 \param length size to send
 \param dest   destination rank
 \param tag    optional tag
 */
void sendSize(const size_t       length,
              const size_t       dest,
              const int          tag  = DefaultTag);

//! MPI_Recv size_t
/**
 \param src source rank
 \param tag optional tag
 \return received size_t
 */
size_t recvSize(const size_t   src,
                const int      tag  = DefaultTag);



//! MPI_Sendrecv size_t
/**
 \param  sendLength size_t to send
 \param  sendRank   destination rank
 \param  recvRank   source rank
 \param sendtag     optional tag
 \param recvtag     optional tag
 \return received size_t
 */
size_t sendRecvSize(const size_t sendLength,
                    const size_t sendRank,
                    const size_t recvRank,
                    const int    sendtag = DefaultTag,
                    const int    recvtag = DefaultTag);

//! MPI_Send bytes
/**
 \param buffer buffer to send
 \param length bytes to send
 \param dest   destination rank
 \param tag    optional tag
 */
void sendBytes(const void * const buffer,
               const size_t       length,
               const size_t       dest,
               const int          tag  = DefaultTag);

//! MPI_Recv bytes
/**
 \param buffer buffer to recv
 \param length bytes to recv
 \param src    source rank
 \param tag    optional tag
 */
void recvBytes(void * const   buffer,
               const size_t   length,
               const size_t   src,
               const int      tag  = DefaultTag);


//! MPI_Sendrecv bytes
/**
 \param sendbuf   send buffer
 \param sendcount bytes to send
 \param dest      destination rank
 \param recvbuf   recv buffer
 \param recvcount bytes to receive
 \param source    source rank
 \param sendtag   optional tag
 \param recvtag   optional tag
 */
void sendrecvBytes(const void * const sendbuf,
                   const size_t       sendcount,
                   const size_t       dest,
                   void * const       recvbuf,
                   const size_t       recvcount,
                   const size_t       source,
                   const int          sendtag = DefaultTag,
                   const int          recvtag = DefaultTag);

//! send one (MPI) object
/**
 \param obj object to send
 \param dst destination rank
 \param tag optional tag
 */
template <typename T> inline
void send1(const T      & obj,
           const size_t   dst,
           const int      tag  = DefaultTag)
{
    static const DataType _ = getDataTypeOf<T>();
    send( &obj, 1, _.dt, sizeof(T), dst, tag);
}

//! receive one (MPI) object
/**
 \param src source rank
 \param tag optional tag
 \return received object
 */
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



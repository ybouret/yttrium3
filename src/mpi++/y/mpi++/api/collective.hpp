
//! MPI_BCast
/**
 \param buffer   I/O buffer
 \param count    count of objects
 \param datatype type of object
 \param bytes    size of buffer
 \param root     sender rank
 */
void bcast(void * const       buffer,
           const size_t       count,
           const MPI_Datatype datatype,
           const uint64_t     bytes,
           const size_t       root);


//! MPI_BCast bytes
/**
 \param buffer   I/O buffer
 \param length   count of bytes
 \param root     sender rank
 */
void bcastBytes(void * const buffer,
                const size_t length,
                const size_t root);


//! broadcasting one type
/**
 \param data I/O data
 \param root sender rank
 */
template <typename T> inline
void bcast1(T             &data,
            const size_t   root)
{
    static const DataType &_ = getDataTypeOf<T>();
    bcast(&data,1,_.dt,sizeof(T),root);
}


void bcast(void * const       buffer,
           const size_t       count,
           const MPI_Datatype datatype,
           const uint64_t     bytes,
           const size_t       root,
           const MPI_Comm     comm = MPI_COMM_WORLD);

template <typename T> inline
void bcast1(T             &data,
            const size_t   root,
            const MPI_Comm comm = MPI_COMM_WORLD)
{
    static const DataType &_ = getDataTypeOf<T>();
    bcast(&data,1,_.dt,sizeof(T),root,comm);
}

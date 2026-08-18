
void send(const void * const buffer,
          const size_t       count,
          const MPI_Datatype datatype,
          const size_t       dest,
          const int          tag = DefaultTag,
          const MPI_Comm     comm = MPI_COMM_WORLD);


void recv(void * const buffer,
          const size_t count,
          const MPI_Datatype datatype,
          const size_t       src,
          const int          tag = DefaultTag,
          const MPI_Comm     comm = MPI_COMM_WORLD);


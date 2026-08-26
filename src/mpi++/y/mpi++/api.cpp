
#include "y/mpi++/api.hpp"
#include "y/type/temporary.hpp"




namespace Yttrium
{
    const char * const MPI:: CallSign = "MPI";

    int MPI:: GetCount(const size_t count, const char * const func)
    {
        assert(func);
        if(count>MaxCount) throw Specific::Exception(func,"count overflow");
        return (int) count;
    }

    MPI:: ~MPI() noexcept
    {
        MPI_Finalize();
    }

    const char *   MPI:: HumanReadableThreadLevel(const int t) noexcept
    {
        switch(t)
        {
                Y_Return_Named_Case(MPI_THREAD_SINGLE);
                Y_Return_Named_Case(MPI_THREAD_FUNNELED);
                Y_Return_Named_Case(MPI_THREAD_SERIALIZED);
                Y_Return_Named_Case(MPI_THREAD_MULTIPLE);
            default:
                break;
        }
        return Core::Unknown;

    }

    namespace
    {
        static bool     __mpi_auth = false;
        static int *    __mpi_argc = 0;
        static char *** __mpi_argv = 0;
        static int      __mpi_cntl = 0;
        static char     __mpi_processor_name[MPI_MAX_PROCESSOR_NAME] = { 0 };
    }

    MPI & MPI:: Init(int *argc, char ***argv, const int required)
    {
        if( Exists() ) throw Specific::Exception(CallSign,"already initialized");

        const Temporary<int>      _1(__mpi_cntl,required);
        const Temporary<int *>    _2(__mpi_argc,argc);
        const Temporary<char ***> _3(__mpi_argv,argv);
        const Temporary<bool>     _4(__mpi_auth,true);


        return Instance();
    }

    MPI:: MPI() :
    Concurrent::Member(1,0),
    threadLevel(-1),
    primary(true),
    replica(false),
    parallel(false),
    sendRate(),
    recvRate(),
    processorName(__mpi_processor_name),
    table()
    {
        if(!__mpi_auth) throw Specific:: Exception(CallSign,"must call Init(...)");

        Y_MPI_Call( MPI_Init_thread(__mpi_argc, __mpi_argv, __mpi_cntl, & Coerce(threadLevel)) );

        {
            int sz = 0;
            Y_MPI_Call( MPI_Comm_size(MPI_COMM_WORLD, &sz) );
            Coerce(size) = (size_t) sz;
        }

        {
            int rk = 0;
            Y_MPI_Call( MPI_Comm_rank(MPI_COMM_WORLD, &rk) );
            Coerce(rank) = (size_t) rk;
            Coerce(indx) = rank+1;
            updateLogo();
        }



        if(0!=rank) CoerceSwap(primary,replica);
        if(size>1)  Coerce(parallel) = true;

        {
            int res = 0;
            Y_MPI_Call( MPI_Get_processor_name(__mpi_processor_name,&res) );
        }

        buildTable();

    }


    namespace
    {
        template <typename T> static inline
        void populate(MPI::DataType::Table & table,
                      const MPI_Datatype     datatype)
        {
            static const size_t   datasize = sizeof(T);
            const String          key = typeid(T).name();
            {
                MPI::DataType * const mdt = table.search(key);
                if(mdt)
                {
                    if( mdt->sz != datasize )
                        throw Specific::Exception(MPI::CallSign, "invalid data size for <%s>", key.c_str());
                    return;
                }
            }

            const MPI::DataType mdt(datatype,datasize);
            if(!table.insert(key,mdt))
                throw Specific::Exception(MPI::CallSign, "failed to populate <%s>", key.c_str());
        }
    }

#define Y_MPI_DECL(type,TYPE) populate<type>(Coerce(table),MPI_##TYPE)

    void MPI:: buildTable()
    {
        Y_MPI_DECL(float,FLOAT);
        Y_MPI_DECL(double,DOUBLE);
        Y_MPI_DECL(long double,LONG_DOUBLE);

        Y_MPI_DECL(char,CHAR);
        Y_MPI_DECL(unsigned char,UNSIGNED_CHAR);

        Y_MPI_DECL(short,SHORT);
        Y_MPI_DECL(unsigned short,UNSIGNED_SHORT);

        Y_MPI_DECL(int,INT);
        Y_MPI_DECL(unsigned,UNSIGNED);

        Y_MPI_DECL(long,LONG);
        Y_MPI_DECL(unsigned long,UNSIGNED_LONG);

        Y_MPI_DECL(long long,LONG);
        Y_MPI_DECL(unsigned long long,UNSIGNED_LONG_LONG);

        Y_MPI_DECL(int8_t, INT8_T);
        Y_MPI_DECL(int16_t,INT16_T);
        Y_MPI_DECL(int32_t,INT32_T);
        Y_MPI_DECL(int64_t,INT64_T);

        Y_MPI_DECL(uint8_t, UINT8_T);
        Y_MPI_DECL(uint16_t,UINT16_T);
        Y_MPI_DECL(uint32_t,UINT32_T);
        Y_MPI_DECL(uint64_t,UINT64_T);

        Y_MPI_DECL(bool,C_BOOL);
        

    }


    const MPI::DataType & MPI:: getDataType(const std::type_info &ti) const
    {
        const String           key = ti.name();
        const DataType * const mdt = table.search(key);
        if(!mdt) throw Specific::Exception(CallSign,"unregistered <%s>", key.c_str());
        return *mdt;
    }

    void MPI:: resetRates() noexcept
    {
        sendRate.ldz();
        recvRate.ldz();
    }


}

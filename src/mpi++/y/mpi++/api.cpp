
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

    void MPI:: barrier()
    {
        Y_MPI_Call( MPI_Barrier(MPI_COMM_WORLD) );
    }


    MPI:: ~MPI() noexcept
    {
        Coerce(table).release(); // because of MPI_Type_free
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

    void MPI:: decl(const std::type_info &tid,
                    const int             count,
                    const int             array_of_block_lengths[],
                    const MPI_Aint        array_of_displacements[],
                    const MPI_Datatype    array_of_types[])
    {
        const String key = tid.name();
        if(table.search(key))
            throw Exception(MPI_ERR_TYPE,"declaring multiple type '%s'", key.c_str() );

        const DataType::Pointer dtp  = new DataType(*this,count,array_of_block_lengths,array_of_displacements,array_of_types);

        if( !Coerce(table).insert(key,dtp) )
            throw Exception(MPI_ERR_TYPE,"failed to register '%s'", key.c_str() );

    }

    const MPI::DataType & MPI:: getDataType(const std::type_info &ti) const
    {
        const String                    key = ti.name();
        const DataType::Pointer * const pdt = table.search(key);
        if(!pdt) throw Specific::Exception(CallSign,"unregistered <%s>", key.c_str());
        return **pdt;
    }

    MPI_Datatype MPI:: _Datatype(const std::type_info &ti) const
    {
        return getDataType(ti).value;
    }


    size_t MPI:: bytesFor(const MPI_Datatype dt) const
    {
        for(DataType::Table::ConstIterator it=table.begin();it!=table.end();++it)
        {
            const MPI::DataType &mdt = **it;
            if(dt==mdt.value)
                return mdt.bytes;
        }
        throw MPI::Exception(MPI_ERR_TYPE, "MPI::bytesFor data: not in table");
    }

    void MPI:: resetRates() noexcept
    {
        sendRate.ldz();
        recvRate.ldz();
    }

}

#include "y/mkl/xreal.hpp"

namespace Yttrium
{
    namespace
    {
        template <typename T> static inline
        void populate(MPI::DataType::Table & table,
                      const MPI_Datatype     datatype)
        {
            static const size_t   datasize = sizeof(T);
            const String          key = typeid(T).name();
            {
                MPI::DataType::Pointer * const pdt = table.search(key);
                if(pdt)
                {
                    if( (**pdt).bytes != datasize )
                        throw Specific::Exception(MPI::CallSign, "invalid data size for <%s>", key.c_str());
                    return;
                }
            }

            const MPI::DataType::Pointer pdt = new MPI::DataType(datatype,datasize);
            if(!table.insert(key,pdt))
                throw Specific::Exception(MPI::CallSign, "failed to populate <%s>", key.c_str());
        }

        template <typename T> static inline
        void populateXReal(MPI &mpi)
        {
            typedef XReal<T> Type;
            mpi.declAsPair<Type>(typeid(T),
                                 offsetof(Type,mantissa),
                                 typeid(int),
                                 offsetof(Type,exponent));
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

        populateXReal<float>(*this);
        populateXReal<double>(*this);
        populateXReal<long double>(*this);


    }





}

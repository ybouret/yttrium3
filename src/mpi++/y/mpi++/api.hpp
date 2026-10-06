//! \file

#ifndef Y_MPI_Included
#define Y_MPI_Included 1

#if defined(_MSC_VER) && (_MSC_VER>1916)
#pragma warning ( disable : 5220 )
#endif

#include "y/string.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/exception.hpp"
#include "y/system/wall-time.hpp"
#include "y/concurrent/member.hpp"
#include "y/container/associative/hash/map.hpp"
#include "y/memory/type/moniker.hpp"
#include "y/format/human-readable.hpp"

#include <typeinfo>

//! disable mpicxx
#define OMPI_SKIP_MPICXX 1

//! disable mpicxx
#define MPICH_SKIP_MPICXX 1


#if defined(Y_WIN) && defined(Y_GNU)
//! disable Microsoft annonations...
#define MSMPI_NO_SAL 1
#endif

#include <mpi.h>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! MPI wrappers in MPI_COMM_WORLD
    //
    //
    //__________________________________________________________________________
    class MPI : public Singleton<MPI,ClassLockPolicy>, public Concurrent::Member
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;                                     //!< "MPI"
        static const Longevity    LifeTime = LifeTimeFor:: MPI;                  //!< Life Time
        static const char *       HumanReadableThreadLevel(const int) noexcept; //!< \return thread level
        static const int          DefaultTag = 1;                               //!< default tag
        static const size_t       MaxCount   = IntegerFor<int>::Maximum;        //!< for int/size_t conversion
        static size_t             ConvertU64ToSize(const uint64_t);             //!< \return converted u64 to size_t, with check
        class ScalarCarrier;
        class VectorCarrier;
        template <typename> class SerialCarrier;

        //______________________________________________________________________
        //
        //
        //! DataType
        //
        //______________________________________________________________________
        class DataType : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            // Definitions
            //__________________________________________________________________
            typedef ArcPtr<DataType>        Pointer; //!< alias
            typedef HashMap<String,Pointer> Table;   //!< hash table of types

            //! identifies genre as BuiltIn or user Defined
            enum Genre
            {
                BuiltIn, //!< pre-committed data type
                Defined  //!< user defined data type
            };


            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________

            //! setup with built-in type and size
            explicit DataType(const MPI_Datatype, const size_t) noexcept;

            //! setup with user's metrics
            /**
             \param mpi instance to get individual bytes
             \param count number of fields in all subsequent arrays, count>0
             \param array_of_block_lengths consecutive block lengths
             \param array_of_displacements  offsets of previous blocks
             \param array_of_types          types of preivous blocks
             */
            explicit DataType(MPI &              mpi,
                              const int          count,
                              const int          array_of_block_lengths[],
                              const MPI_Aint     array_of_displacements[],
                              const MPI_Datatype array_of_types[]);

            virtual ~DataType()                        noexcept; //!< cleanup

            const MPI_Datatype value; //!< the data type value
            const size_t       bytes; //!< bytes per transmitted item
            const Genre        genre; //!< type genre

        private:
            Y_Disable_Copy_And_Assign(DataType); //!< discard
        };

        //______________________________________________________________________
        //
        //
        //! Carrier interface
        //
        //______________________________________________________________________
        class  Carrier : public CountedObject
        {
        public:
            //______________________________________________________________________
            //
            //
            // Definitions
            //
            //______________________________________________________________________
            typedef ArcPtr<Carrier>        Handle; //!< alias
            typedef HashMap<String,Handle> Table;  //!< alias

            //______________________________________________________________________
            //
            //
            // C++
            //
            //______________________________________________________________________
            explicit Carrier() noexcept; //!< setup
            virtual ~Carrier() noexcept; //!< cleanup

            //______________________________________________________________________
            //
            //
            // Interface
            //
            //______________________________________________________________________


            //! send array of objects
            /**
             \param mpi    instance
             \param entry  first object address
             \param items  number of objects
             \param target target rank
             \param tag    channel
             */
            virtual void send(MPI &              mpi,
                              const void * const entry,
                              const size_t       items,
                              const size_t       target,
                              const int          tag) = 0;

            //! receive array of objects
            /**
             \param mpi    instance
             \param entry  first object address
             \param items  number of objects
             \param source source rank
             \param tag    channel
             */
            virtual void recv(MPI &         mpi,
                              void * const  entry,
                              const size_t  items,
                              const size_t  source,
                              const int     tag) = 0;


        private:
            Y_Disable_Copy_And_Assign(Carrier); //!< discarded
        };


        //______________________________________________________________________
        //
        //
        //! Rate for statistics
        //
        //______________________________________________________________________
        class Rate
        {
        public:
            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            Rate()                         noexcept; //!< setup
            ~Rate()                        noexcept; //!< cleanup
            Rate(const Rate &)             noexcept; //!< duplicate
            Rate & operator=(const Rate &) noexcept; //!< assign \return *this

            //__________________________________________________________________
            //
            // Methods
            //__________________________________________________________________
            void          ldz()                      noexcept; //!< reset
            HumanReadable hrt(const System::WallTime &) const; //!< return readable rate
            String        str(const System::WallTime &) const; //!< return printable string

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            uint64_t bytes; //!< cumulative bytes
            uint64_t ticks; //!< cumulative ticks
        };

        //______________________________________________________________________
        //
        //
        //! Exception
        //
        //______________________________________________________________________
        class Exception : public Yttrium:: Exception
        {
        public:
            //! setup \param err error code \param fmt C-style format
            Exception(const int err, const char * fmt,...) noexcept Y_Printf_Check(3,4);
            Exception(const Exception &) noexcept;      //!< duplicate
            virtual ~Exception()         noexcept;      //!< cleanup

        private:
            Y_Disable_Assign(Exception); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! MPI_Init, wrapper
        /**
         \param argc     for MPI_Init_Thread
         \param argv     for MPI_Init_Thread
         \param required for MPI_Init_Thread
         \return MPI instance, initialized
         */
        static MPI & Init(int *argc, char ***argv, const int required = MPI_THREAD_SINGLE);

        //! convert size to int
        /**
         \param count users's count
         \param func  name of the function where conversion occurs
         \return converted with checkw
         */
        static int GetCount(const size_t count, const char * const func);

        //! MPI_Barrier(MPI_COMM_WORLD)
        void barrier();

        //! \return data type from type info of MPI supported type
        const DataType & getDataType(const std::type_info &) const;

        //! \return data type from type of T
        template <typename T> inline
        const DataType & getDataTypeOf() const {
            static const DataType & _ = getDataType(typeid(T));
            return _;
        };

        //! \return retrieve matching datatype
        MPI_Datatype _Datatype(const std::type_info &) const;

        //! \return matching MPI_Datatype
        template <typename T>
        inline MPI_Datatype _DatatypeOf() const
        {
            static const MPI_Datatype _ = _Datatype( typeid(T) );
            return _;
        }

        //! \return bytes for given MPI_Datatype, throw if not found
        size_t bytesFor(const MPI_Datatype) const;

        //! define a new type
        /**
         \param tid new type identifier
         \param count                  see DataType(...)
         \param array_of_block_lengths see DataType(...)
         \param array_of_displacements see DataType(...)
         \param array_of_types         see DataType(...)
         */
        void decl(const std::type_info &tid,
                  const int             count,
                  const int             array_of_block_lengths[],
                  const MPI_Aint        array_of_displacements[],
                  const MPI_Datatype    array_of_types[]);


        //! helper to define a new type
        template <typename T> inline
        void decl(const int             count,
                  const int             array_of_block_lengths[],
                  const MPI_Aint        array_of_displacements[],
                  const MPI_Datatype    array_of_types[])
        {
            decl(typeid(T),count,array_of_block_lengths,array_of_displacements,array_of_types);
        }

        //! helper to define a new heterogeneous pair
        template <typename T> inline
        void declAsPair(const std::type_info &u,
                        const MPI_Aint        uoff,
                        const std::type_info &v,
                        const MPI_Aint        voff)
        {
            static const int   count = 2;
            static const int   array_of_block_lengths[] = {1,1};
            const MPI_Aint     array_of_displacements[] = {uoff,voff};
            const MPI_Datatype array_of_types[]         = {_Datatype(u), _Datatype(v) };
            decl<T>(count,array_of_block_lengths,array_of_displacements,array_of_types);
        }


        //______________________________________________________________________
        //
        //
        // Peer To Peer API
        //
        //______________________________________________________________________
#include "y/mpi++/api/p2p.hpp"


        //______________________________________________________________________
        //
        //
        // Collective API
        //
        //______________________________________________________________________
#include "y/mpi++/api/collective.hpp"

        //______________________________________________________________________
        //
        //
        // Helpers to sync
        //
        //______________________________________________________________________
        void syncWith(const size_t peer); //!< ack/syn       \param peer peer rank
        void ack(const size_t peer);      //!< send one byte \param peer peer rank
        void syn(const size_t peer);      //!< recv one byte \param peer peer rank
        void resetRates() noexcept;       //!< reset all rates


        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const int             threadLevel;   //!< current thread level
        const bool            primary;       //!< primary flag
        const bool            replica;       //!< replica flag
        const bool            parallel;      //!< size>1
        Rate                  sendRate;      //!< sending rate
        Rate                  recvRate;      //!< receiving rate
        const char * const    processorName; //!< MPI_GetProcessorName
        const DataType::Table dataTypes;     //!< table of data types
        const Carrier::Table  carriers;      //!< table of carriers
        
    private:
        Y_Disable_Copy_And_Assign(MPI); //!< discarded
        friend class Singleton<MPI,ClassLockPolicy>;
        virtual ~MPI() noexcept; //!< cleanup: MPI_Finalize()
        explicit MPI();          //!< setup from Initialize(...)
        void buildDataTypes();   //!< build table of supported MPI data type
    };

    //! helper to handle errors
#define Y_MPI_Call( CODE ) do { \
/**/ const int err = CODE;      \
/**/ if( MPI_SUCCESS != err ) throw MPI::Exception(err,"in '%s'",#CODE); \
} while(false)

#define Y_MPI_Mark() const uint64_t __mark__ = System::WallTime::Ticks() //!< helper
#define Y_MPI_Gain() (System::WallTime::Ticks() - __mark__)              //!< helper


    //! in order CODE with mpi_ = THE_MPI
#define  Y_MPI_ForEach(THE_MPI,CODE) do \
/**/    { \
/**/        MPI &mpi_ = (THE_MPI); \
/**/        mpi.barrier(); \
/**/        if(mpi_.primary) \
/**/        {\
/**/            do { CODE; } while(false); \
/**/            for(size_t rank=1;rank<mpi_.size;++rank) \
/**/                mpi_.syncWith(rank);\
/**/        }\
/**/        else\
/**/        {\
/**/            mpi_.syn(0);\
/**/            do { CODE; } while(false); \
/**/            mpi_.ack(0);\
/**/        }\
/**/    } while(false)

    //! execute CODE only on primary node
#define Y_MPI_Trace(THE_MPI,CODE) do                        \
/**/    {                                                   \
/**/        MPI &mpi_ = (THE_MPI);                          \
/**/        mpi_.barrier();                                 \
/**/        if(mpi_.primary) { do { CODE; } while(false); } \
/**/    } while(false)
}


#endif // !Y_MPI_Included

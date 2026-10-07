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
#include "y/stream/memory/output.hpp"
#include "y/stream/memory/input.hpp"
#include "y/type/alternative.hpp"

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

#include "y/mpi++/api/data-type.hpp"
#include "y/mpi++/api/rate.hpp"

#include "y/mpi++/carrier/interface.hpp"
#include "y/mpi++/carrier/serial.hpp"



        template <typename T, typename = int>
        struct HasDIMENSIONS { static const bool Value = false; };

        template <typename T>
        struct HasDIMENSIONS <T, decltype((void) T::DIMENSIONS, 0)>
        {
            static const bool Value = true;
        };

        template <typename T>
        struct SerialCarrierAPI
        {
            static inline Carrier & Get(MPI &mpi) { return mpi.getSerialCarrier<T>(); }
        };

        template <typename T>
        struct VectorCarrierAPI
        {
            static inline Carrier & Get(MPI &mpi) { return mpi.getVectorCarrier<T>(); }
        };

        template <typename T>
        struct ScalarCarrierAPI
        {
            static inline Carrier & Get(MPI &mpi) { return mpi.getScalarCarrier<T>(); }
        };

        
        template <typename T>
        struct SelectCarrier
        {
            static const bool UseSerial = Y_Is_SuperSubClass_Strict(Serializable,T);
            static const bool UseVector = HasDIMENSIONS<T>::Value;
            typedef typename Alternative<
            UseSerial,SerialCarrierAPI<T>,
            UseVector,VectorCarrierAPI<T>,
            ScalarCarrierAPI<T>
            >::Type API;
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
        void barrier();                   //!< MPI_Barrier(MPI_COMM_WORLD)
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




#if !defined(_MSC_VER)

    //! helper to declare specific Read function
#define Y_MPI_Serial_Decl(CLASS)                    \
/**/ template<> MPI::SerialCarrier<CLASS>::ReadProc \
/**/ const      MPI::SerialCarrier<CLASS>::Read


    namespace Apex { class Natural; class Integer; class Rational; }
    Y_MPI_Serial_Decl(Apex::Natural);  //!< Read for apn
    Y_MPI_Serial_Decl(Apex::Integer);  //!< Read for apz
    Y_MPI_Serial_Decl(Apex::Rational); //!< Read for apq
    Y_MPI_Serial_Decl(String);         //!< Read for String

#endif // !defined(_MSC_VER)

}

#endif // !Y_MPI_Included

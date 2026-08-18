
#ifndef Y_MPI_Included
#define Y_MPI_Included 1

#if defined(_MSC_VER) && (_MSC_VER>1916)
#pragma warning ( disable : 5220 )
#endif

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/exception.hpp"
#include "y/system/wall-time.hpp"

#include "y/string.hpp"

#include "y/concurrent/member.hpp"



#include <typeinfo>

//! disable mpicxx
#define OMPI_SKIP_MPICXX 1

//! disable mpicxx
#define MPICH_SKIP_MPICXX 1

#include <mpi.h>

namespace Yttrium
{

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

        const int           threadLevel;   //!< current thread level
        const bool          primary;       //!< primary flag
        const bool          replica;       //!< replica flag
        const bool          parallel;      //!< size>1
        Rate                sendRate;      //!< sending rate
        Rate                recvRate;      //!< receiving rate
        const char * const  processorName; //!< MPI_GetProcessorName

    private:
        Y_Disable_Copy_And_Assign(MPI);
        friend class Singleton<MPI,ClassLockPolicy>;
        virtual ~MPI() noexcept;
        explicit MPI();
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
}


#endif // !Y_MPI_Included


//! \file

#ifndef Y_Concurrent_Thread_Venue_Included
#define Y_Concurrent_Thread_Venue_Included 1

#include "y/handy/basic/heavy/list.hpp"
#include "y/string.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        typedef Handy::BasicHeavyList<size_t> VList; //!< alias
        typedef VList::NodeType               VNode; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Low Level List of CPU index(ices)
        //
        //
        //______________________________________________________________________
        class VenueList : public CountedObject, public VList
        {
        public:
            explicit VenueList() noexcept; //!< setup emptu
            virtual ~VenueList() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(VenueList); //!< discarded
        };

        typedef ArcPtr<VenueList> SharedVList; //!< alias


        //______________________________________________________________________
        //
        //
        //
        //! (shared) list of cpu to use per thread
        //
        //
        //______________________________________________________________________
        class Venue : public SharedVList
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;    //!< "Y_NUM_THREADS"
            static const char         COLON = ':'; //!< alias for encoded
            static const char         COMA  = ','; //!< alias for listing

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            /** setup
             \param ncpu number of cpu
             - if cpu>0, then venue is linear from [0:cpu-1]
             - otherwise, Y_NUM_THREADS is parsed:
             -- if it doesn't exist, use linear on hardware detected cores
             -- if matches, use "CPUS[:OFFSET[:STEP]]"
             -- if matches, use "CPU0[,CPU1[,...]"
             */
            Venue(const size_t ncpu=0);
            Venue(const Venue &) noexcept; //!< duplicate (shared copy)
            virtual ~Venue()     noexcept; //!< cleanup

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        private:
            Y_Disable_Assign(Venue);
            void parse(String &);
            void linear(const size_t);
            void parseCode(const String&);
            void parseList(const String&);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };


    }

}

#endif // !Y_Concurrent_Thread_Venue_Included


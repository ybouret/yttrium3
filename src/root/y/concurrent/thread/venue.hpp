
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
        typedef Handy::BasicHeavyList<size_t> VList;
        typedef VList::NodeType               VNode;

        class VenueList : public CountedObject, public VList
        {
        public:
            explicit VenueList() noexcept;
            virtual ~VenueList() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(VenueList);
        };

        typedef ArcPtr<VenueList> SharedVList;

        class Venue : public SharedVList
        {
        public:
            static const char * const CallSign;    //!< "Y_NUM_THREADS"
            static const char         COLON = ':'; //!< alias
            static const char         COMA  = ';'; //!< alias

            Venue(const size_t ncpu=0);
            Venue(const Venue &) noexcept;
            virtual ~Venue() noexcept;
            
        private:
            Y_Disable_Assign(Venue);
            void parse(String &);
            void linear(const size_t);
            void parseCode(const String&);
            void parseList(const String&);
        };


    }

}

#endif // !Y_Concurrent_Thread_Venue_Included


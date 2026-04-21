

//! \file

#ifndef Y_Concurrent_Subdivision_Included
#define Y_Concurrent_Subdivision_Included 1

#include "y/concurrent/member.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Subdivision interface
        //
        //
        //______________________________________________________________________
        class Subdivision : public Member
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param sz size \param rk rank
            explicit Subdivision(const size_t sz, const size_t rk) noexcept;
            virtual ~Subdivision() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool isEmpty() const noexcept = 0; //!< \return true iff empty subdivision

        private:
            Y_Disable_Copy_And_Assign(Subdivision); //!< discarded
        };

    }

}

#endif // !Y_Concurrent_Subdivision_Included


//! \file

#ifndef Y_Concurrent_Subdivision_Included
#define Y_Concurrent_Subdivision_Included 1

#include "y/concurrent/api/context.hpp"

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
        class Subdivision : public Context
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param sz size \param rk rank \param lk PERSISTENT lock
            explicit Subdivision(const size_t sz,
                                 const size_t rk,
                                 Lockable    &lk) noexcept;
            explicit Subdivision(const Context &) noexcept; //!< setup from context
            virtual ~Subdivision() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool isEmpty() const noexcept = 0; //!< \return true iff empty subdivision

            template <typename T> inline
            T & as() noexcept {
                assert(bytes>=sizeof(T));
                return *static_cast<T*>(entry);
            }

            template <typename T> inline
            const T & as() const noexcept {
                assert(bytes>=sizeof(T));
                return *static_cast<const T*>(entry);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            void * const entry; //!< local cache entry
            const size_t bytes; //!< local cache bytes

        private:
            Y_Disable_Copy_And_Assign(Subdivision); //!< discarded
        };

    }

}

#endif // !Y_Concurrent_Subdivision_Included


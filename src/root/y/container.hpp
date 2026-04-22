//! \file

#ifndef Y_Container_Included
#define Y_Container_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! base class for containers
    //
    //
    //__________________________________________________________________________
    class Container
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Container() noexcept;

    public:
        virtual ~Container() noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual size_t size()     const noexcept = 0; //!< \return current item count
        virtual size_t capacity() const noexcept = 0; //!< \return maximum item count

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        size_t available() const noexcept; //!< \return capacity() - size()

        //! compute next capacity
        /**
         \param n current capacity
         \return logarithmicly increased required capacity
         */
        static size_t NextCapacity(const size_t n);

    private:
        Y_Disable_Copy_And_Assign(Container); //!< discarded
    };

}

#endif // !Y_Container_Included


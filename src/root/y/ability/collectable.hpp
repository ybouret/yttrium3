//! \file

#ifndef Y_Collectable_Included
#define Y_Collectable_Included 1

#include "y/ability/releasable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! May collect some garbage
    //
    //
    //__________________________________________________________________________
    class Collectable : public Releasable
    {
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
    public:
        static const uint8_t All = 0xff; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Collectable() noexcept; //!< setup
    public:
        virtual ~Collectable() noexcept; //!< cleanup


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! garbace collector for amount
        /**
         \param amount in  0 (none) to 0xff (all) of content
         */
        virtual void gc(const uint8_t amount) noexcept = 0;

        //! gc(All), may be overriden
        virtual void release() noexcept;


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! compute new size after garbage collection
        /**
         \param garbageAmount  garbage amount in [0x00:0xff]
         \param oldSize        number of items
         \return new size from kept amount
         */
        static size_t NewSize(const uint8_t garbageAmount, const size_t oldSize) noexcept;




    private:
        Y_Disable_Copy_And_Assign(Collectable); //!< discarding
    };

}

#endif // !Y_Collectable_Included

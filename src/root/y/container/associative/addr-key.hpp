
//! \file

#ifndef Y_Associative_AddrKey_Inluded
#define Y_Associative_AddrKey_Inluded 1

#include "y/type/args.hpp"
#include "y/type/ints.hpp"
#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Convert address into key
    //
    //
    //__________________________________________________________________________
    class AddrKey : public Memory::ReadOnlyBuffer
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const size_t Length = sizeof(void*);     //!< alias
        typedef UnsignedFor<Length>::Alias::Type UType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param ref reference to use address from
        template <typename T> inline
        explicit AddrKey(T &ref) noexcept :
        data()
        {
            fillWith( &ref );
        }
        AddrKey(const AddrKey &) noexcept; //!< duplicate
        virtual ~AddrKey()       noexcept; //!< cleanup
        Y_OSTREAM_PROTO(AddrKey);          //!< display

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const void * ro()     const noexcept;
        virtual size_t       length() const noexcept;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \return true iff same data
        friend bool operator==(const AddrKey&, const AddrKey&) noexcept;

    private:
        Y_Disable_Assign(AddrKey);                  //!< discarded
        void fillWith(const void * const) noexcept; //!< initialize
        uint8_t data[Length];                       //!< inner key
    };

}

#endif // !Y_Associative_AddrKey_Inluded

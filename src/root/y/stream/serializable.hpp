
//! file

#ifndef Y_Serializable_Included
#define Y_Serializable_Included 1

#include "y/config/setup.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{

    class OutputStream;

    //__________________________________________________________________________
    //
    //
    //
    //! Serializable interface
    //
    //
    //__________________________________________________________________________
    class Serializable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Serializable() noexcept;
    public:
        virtual ~Serializable() noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        //! write binary, portable representation \return written bytes
        virtual size_t serialize(OutputStream &) const = 0;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        size_t saveBinary(const char * const         fileName) const;
        size_t saveBinary(const Core::String<char> & filename) const;

    private:
        Y_Disable_Copy_And_Assign(Serializable); //!< discarded
    };

}

#endif // !Y_Serializable_Included


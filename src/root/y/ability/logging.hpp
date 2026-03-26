

//! \file

#ifndef Y_Logging_Included
#define Y_Logging_Included 1

#include "y/config/setup.hpp"
#include <iosfwd>

namespace Yttrium
{
    namespace XML { class Log; }

    //__________________________________________________________________________
    //
    //
    //
    //! XML logging ability
    //
    //
    //__________________________________________________________________________
    class Logging
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Logging() noexcept; //!< initialize
    public:
        virtual ~Logging() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! write as XML description \param xml target
        virtual void toXML(XML::Log &xml) const = 0;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! write XML to output \return given output
        std::ostream & writeXML(std::ostream &) const;

    private:
        Y_Disable_Copy_And_Assign(Logging); //!< discarding


    };


}

#endif // !Y_Logging_Included


//! \file

#ifndef Y_Exception_Included
#define Y_Exception_Included 1

#include "y/config/setup.hpp"
#include <exception>

namespace Yttrium
{
    class Exception : public std::exception
    {
    public:
        static const size_t Length = 256;

        explicit Exception() noexcept;
        virtual ~Exception() noexcept;

        virtual const char * what() const noexcept;

    private:
        void ldz() noexcept;
        char when_[Length];
        char what_[Length];
    };
}

#endif // !Y_Exception_Included



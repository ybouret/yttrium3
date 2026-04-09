

//! \file

#ifndef Y_Writable_Container_Included
#define Y_Writable_Container_Included 1

#include "y/container/readable.hpp"

namespace Yttrium
{

    template <typename T>
    class Writable : public Readable<T>
    {
    public:
        typedef typename Readable<T>::Type Type;

        inline explicit Writable() noexcept {}
        inline virtual ~Writable() noexcept {}

        inline Type & operator[](const size_t indx) noexcept
        {
            assert(indx>=1); assert(indx<=this->size());
            return (Type&)(this->ask(indx));
        }

    private:
        Y_Disable_Copy_And_Assign(Writable);
    };

}

#endif // !Y_Writable_Container_Included


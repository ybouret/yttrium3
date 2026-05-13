
//! \file

#ifndef Y_Container_Ordered_Included
#define Y_Container_Ordered_Included 1


#include "y/container.hpp"
#include "y/type/args.hpp"
#include "y/ability/recyclable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Ordered container interface
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Ordered : public Container, public Recyclable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit Ordered() noexcept : Container() {} //!< setup
        inline virtual ~Ordered() noexcept               {} //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interfac
        //
        //______________________________________________________________________
        virtual void        push(ParamType)       = 0; //!< insert new item
        virtual void        pop()        noexcept = 0; //!< remove top titem
        virtual ConstType & peek() const noexcept = 0; //!< \return top item

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! extract first node \return saved content, queue is popped
        inline Type pull()
        {
            ConstType saved = peek();
            pop();
            return saved;
        }

        //! helper to push \param data new data \return *this
        inline Ordered<T> & operator<<(ParamType data)
        {
            push(data);
            return *this;
        }

    private:
        Y_Disable_Copy_And_Assign(Ordered); //!< discarded
    };
}

#endif // !Y_Container_Ordered_Included



//! \file

#ifndef Y_Readable_Container_Included
#define Y_Readable_Container_Included 1

#include "y/container.hpp"
#include "y/type/args.hpp"
#include <iostream>
#include <cassert>

#if defined(_MSC_VER)
#pragma warning ( disable : 4435 )
#endif

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Readable container
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Readable : public virtual Container
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit Readable() noexcept {} //!< setup
        inline virtual ~Readable() noexcept {} //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! const access \param indx in [1:size()] \return indx-th item
        inline ConstType & operator[](const size_t indx) const noexcept
        {
            assert(indx>=1); assert(indx<=size());
            return ask(indx);
        }

        //! default display
        inline friend std::ostream & operator<<(std::ostream &os, const Readable &self)
        {
            os << '[';
            const size_t n = self.size();
            if(n>0)
            {
                os << self[1];
                for(size_t i=2;i<=n;++i) os << ';' << self[i];
            }
            return os << ']';
        }


    private:
        Y_Disable_Copy_And_Assign(Readable); //!< discarded

    protected:
        //! ask item \param indx indx in [1:size()] \return item at given index
        virtual ConstType & ask(const size_t indx) const noexcept = 0;
    };

    //! helper to declare as Readable
#define Y_Readable_Decl() virtual ConstType & ask(const size_t) const noexcept

}

#endif // !Y_Readable_Container_Included


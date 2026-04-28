//! \file

#ifndef Y_Type_Proxy_Included
#define Y_Type_Proxy_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Proxy to interface
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Proxy
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Interface); //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit Proxy() noexcept {} //!< setup
        inline virtual ~Proxy() noexcept {} //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline Interface *      operator->()       noexcept { return & (Interface&)locus(); } //!< \return access
        inline ConstInterface * operator->() const noexcept { return & locus(); }             //!< \return const access

        //! forward call
        inline friend std::ostream & operator<<(std::ostream &os, const Proxy &self)
        {
            return os << self.locus();
        }


    private:
        Y_Disable_Copy_And_Assign(Proxy); //!< discarding

        //! \return interface location
        virtual ConstInterface & locus() const noexcept = 0;
    };


    //! helper to declare Proxy
#define Y_Proxy_Decl() virtual ConstInterface & locus() const noexcept

    //! helper to implement Proxy
#define Y_Proxy_Impl(CLASS,LOCUS) \
CLASS::ConstInterface  & CLASS :: locus() const noexcept { return LOCUS; }

}

#endif // !Y_Type_Proxy_Included


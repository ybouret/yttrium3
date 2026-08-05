
//! \file

#ifndef Y_Type_VaArgs_Included
#define Y_Type_VaArgs_Included 1

#include "y/type/va/list.hpp"

namespace Yttrium
{

    class VaArgs
    {
    public:
        VaArgs(VaList &) noexcept;
        ~VaArgs() noexcept;

        size_t   codeBytes() const noexcept; //!< \return bytes still containing code

        //! unpack data \return cast a previously stored args
        template <typename T> inline
        T & as() noexcept
        {
            return *static_cast<T*>( unpack() );
        }

        //! unpack a C-style function \return cast of previously stored function address
        template <typename CFUNCTION> inline
        CFUNCTION func()
        {
            union {
                void *    addr;
                CFUNCTION func;
            } alias = { unpack() }; assert(0!=alias.func);
            return alias.func;
        }


        //! unpack a memthod pointer \return cat of previously stored method pointer
        template <typename METHOD> inline
        METHOD meth() noexcept
        {
            assert(sizeof(METHOD)==sizeof(VaList::Meth));
            union { METHOD user; } alias = { 0 };
            mquery(&alias);
            return alias.user;
        }

    private:
        Y_Disable_Copy_And_Assign(VaArgs);
        VaList  & list;
        uint8_t * rptr;

        void   * unpack()             noexcept; //!< \return decoded address
        void     mquery(void * const) noexcept; //!< decode method at given address

    };

}


#endif // !Y_Type_VaArgs_Included


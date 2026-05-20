
//! \file

#ifndef Y_Hashing_KeyDumper_Included
#define Y_Hashing_KeyDumper_Included 1


#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Hashing
    {

        //______________________________________________________________________
        //
        //
        //
        //! Primitive type dumping
        //
        //
        //______________________________________________________________________
        template <typename T>
        class KeyDumper
        {
        public:
            inline  KeyDumper() noexcept {} //!< setup
            inline ~KeyDumper() noexcept {} //!< cleanup

            //! \param k integral value \return key
            inline size_t operator()(const T &k) noexcept
            {
                return (size_t)k;
            }

        private:
            Y_Disable_Copy_And_Assign(KeyDumper); //!< discarded
        };

    }

}

#endif // !Y_Hashing_KeyDumper_Included

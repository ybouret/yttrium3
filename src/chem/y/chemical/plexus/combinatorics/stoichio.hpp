
#ifndef Y_Chemical_Stoichio_Included
#define Y_Chemical_Stoichio_Included 1

#include "y/container/cxx/array.hpp"
#include "y/core/list/cxx.hpp"
#include "y/type/proxy.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef CxxArray<int> iArray; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! dynamic array of coefficients
        //
        //
        //______________________________________________________________________
        class Stoichio : public Object, public iArray
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxListOf<Stoichio> List; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Stoichio(const iArray &); //!< setup
            virtual ~Stoichio() noexcept;      //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Stoichio *next; //!< for list
            Stoichio *prev; //!< for list

        private:
            Y_Disable_Copy_And_Assign(Stoichio); //!< discarded
        };

        //______________________________________________________________________
        //
        //
        //
        //! Database of unique arrays of coefficients
        //
        //
        //______________________________________________________________________
        class StoichioDB : public Proxy<const Stoichio::List>
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit StoichioDB() noexcept;
            virtual ~StoichioDB() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool mayUse(const iArray &); //!< \return true iff new unique array

        private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_Disable_Copy_And_Assign(StoichioDB);
            Y_Proxy_Decl();
            CxxListOf<Stoichio> list;
#endif
        };

    }

}

#endif // !Y_Chemical_Stoichio_Included



//! \file

#ifndef Y_Memory_Moniker_Included
#define Y_Memory_Moniker_Included 1


#include "y/memory/type/embedded.hpp"
#include "y/calculus/alignment.hpp"
#include <iostream>

namespace Yttrium
{

    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Static buffer for a type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class MonikerData
        {
        public:
            inline virtual ~MonikerData() noexcept          {} //!< cleanup
        protected:
            inline explicit MonikerData() noexcept : wksp() {} //!< setup

            void *wksp[ Alignment::WordsFor<T>::Count ]; //!< inner static buffer
        private:
            Y_Disable_Copy_And_Assign(MonikerData); //!< discarded
        };

        //______________________________________________________________________
        //
        //
        //
        //! Static embedded type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Moniker : public MonikerData<T>, public Embedded<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            using MonikerData<T>::wksp;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with default constructor
            inline explicit Moniker() : MonikerData<T>(), Embedded<T>(wksp) { }

            //! cleanup
            inline virtual ~Moniker() noexcept {}

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename U>
            inline explicit Moniker(U &u) :
            MonikerData<T>(), Embedded<T>(wksp,u) { }


            template <typename U, typename V>
            inline explicit Moniker(U &u, V &v) :
            MonikerData<T>(), Embedded<T>(wksp,u,v) { }

            template <typename U, typename V, typename W>
            inline explicit Moniker(U &u, V &v, W &w) :
            MonikerData<T>(), Embedded<T>(wksp,u,v,w) { }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        private:
            Y_Disable_Copy_And_Assign(Moniker); //!< discarded


        };
    }

}

#endif // !Y_Memory_Moniker_Included


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

        template <typename T>
        class MonikerData
        {
        public:
            inline virtual ~MonikerData() noexcept {}
        protected:
            inline explicit MonikerData() noexcept : wksp()
            {
            }

            void *wksp[ Alignment::WordsFor<T>::Count ];
        private:
            Y_Disable_Copy_And_Assign(MonikerData);
        };

        template <typename T>
        class Moniker : public MonikerData<T>, public Embedded<T>
        {
        public:
            Y_Args_Expose(T,Type);
            using MonikerData<T>::wksp;

            inline explicit Moniker() : MonikerData<T>(), Embedded<T>(wksp) { }

            inline virtual ~Moniker() noexcept {}

            template <typename U>
            inline explicit Moniker(U &u) :
            MonikerData<T>(), Embedded<T>(wksp,u) { }


            template <typename U, typename V>
            inline explicit Moniker(U &u, V &v) :
            MonikerData<T>(), Embedded<T>(wksp,u,v) { }

            template <typename U, typename V, typename W>
            inline explicit Moniker(U &u, V &v, W &w) :
            MonikerData<T>(), Embedded<T>(wksp,u,v,w) { }

        private:
            Y_Disable_Copy_And_Assign(Moniker);


        };
    }

}

#endif // !Y_Memory_Moniker_Included

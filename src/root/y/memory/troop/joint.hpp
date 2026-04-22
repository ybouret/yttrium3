//! \file

#ifndef Y_Memory_JointTroop_Included
#define Y_Memory_JointTroop_Included 1

#include "y/memory/troop.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/block/move.h"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Troop with operation on head
        //
        //
        //______________________________________________________________________
        template <typename T>
        class JointTroop : public Troop<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases
            using Troop<T>::addr;
            using Troop<T>::size;
            using Troop<T>::capacity;
            using Troop<T>::cxx;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit JointTroop(const size_t n) : Troop<T>(n) {} //!< setup \param n minimal capacity
            inline virtual ~JointTroop() noexcept                    {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! push any compatible value at head \param args compatible value
            template <typename ARGS>
            inline void pushHead(const ARGS &args)
            {
                assert(size<capacity);
                void *              wksp[ Alignment::WordsFor<T>::Count ];
                MutableType * const temp = new ( Y_BZero(wksp) ) MutableType(args);
                Yttrium_BMove(addr+1,addr,sizeof(T) * Coerce(size)++ );
                Yttrium_BCopy(addr,temp,sizeof(T));
                Y_BZero(wksp);
            }

            //! remove head element
            inline void popHead() noexcept
            {
                assert(size>0);
                MutableType * const target = addr;
                Yttrium_BMove(Destructed(target),target+1,--Coerce(size) * sizeof(T) );
                Yttrium_BZero(target+size,sizeof(T));
            }

            //! remove indx-th element \param indx in [1:size]
            inline void remove(const size_t indx) noexcept
            {
                assert(indx>=1);
                assert(indx<=size);
                MutableType * const target = cxx+indx;
                Yttrium_BMove(Destructed(target),target+1, (Coerce(size)-- - indx) * sizeof(T) );
                Yttrium_BZero(addr+size,sizeof(T));
            }

            //! demote indx-th element \param indx in [1:size]
            inline void demote(const size_t indx) noexcept
            {
                assert(indx>=1);
                assert(indx<=size);
                assert(cxx+1==addr);
                void *              wksp[ Alignment::WordsFor<T>::Count ];
                void * const        save   = Y_BZero(wksp);
                MutableType * const target = cxx+indx;
                Yttrium_BCopy(save,target,sizeof(T));
                Yttrium_BMove(target,target+1,(size-indx)*sizeof(T));
                Yttrium_BCopy(cxx+size,save,sizeof(T));
                Y_BZero(wksp);
            }


        private:
            Y_Disable_Copy_And_Assign(JointTroop); //!< discarded
        };
    }

}

#endif // !Y_Memory_JointTroop_Included


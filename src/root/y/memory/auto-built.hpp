//! \file

#ifndef Y_Memory_AutoBuilt_Included
#define Y_Memory_AutoBuilt_Included 1

#include "y/memory/auto-build.hpp"
#include "y/type/args.hpp"
#include "y/type/procedural.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Built array of types with user's specifications
        //
        //
        //______________________________________________________________________
        template <typename T>
        class AutoBuilt : public AutoBuild
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with default constructor
            /**
             - userBlockAddr must have at least userNumBlocks * sizeof(T)
             \param userBlockAddr where to build
             \param userNumBlocks blocks to build
             */
            inline explicit AutoBuilt(void * const userBlockAddr,
                                      const size_t userNumBlocks) :
            AutoBuild(userBlockAddr,userNumBlocks,sizeof(T),OnDelete,OnBuild0)
            {
            }

            //! setup with one argument constructor
            /**
             - userBlockAddr must have at least userNumBlocks * sizeof(T)
             - MutableType(arg1) called for each type
             \param userBlockAddr where to build
             \param userNumBlocks blocks to build
             \param arg1          argument to build
             */
            template <typename U>
            inline explicit AutoBuilt(void * const userBlockAddr,
                                      const size_t userNumBlocks,
                                      U &          arg1) :
            AutoBuild(userBlockAddr,userNumBlocks,sizeof(T),OnDelete,OnBuild1<U>,(void*)&arg1)
            {
            }


            //! setup with one indexed argument constructor
            /**
             - userBlockAddr must have at least userNumBlocks * sizeof(T)
             - MutableType(arr[indx]) called for each type
             \param userBlockAddr where to build
             \param userNumBlocks blocks to build
             \param arr           array[1:numBlocks] to build
             */
            template <typename ARR>
            inline explicit AutoBuilt(const Procedural_ &,
                                      void * const userBlockAddr,
                                      const size_t userNumBlocks,
                                      ARR &        arr) :
            AutoBuild(userBlockAddr,userNumBlocks,sizeof(T),OnDelete,OnBuildN<ARR>,(void*)&arr)
            {
            }

            //! cleanup
            inline virtual ~AutoBuilt() noexcept
            {
            }

        private:
            Y_Disable_Copy_And_Assign(AutoBuilt); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static inline void OnBuild0(void * const addr)
            {
                new (addr) MutableType();
            }

            static inline void OnDelete(void * const addr) noexcept
            {
                assert(0!=addr);
                Destruct( static_cast<MutableType *>(addr) );
            }

            template <typename U>
            static inline void OnBuild1(void * const addr, void * const arg1)
            {
                assert(0!=arg1);
                U &u  = *static_cast<U*>(arg1);
                new (addr) MutableType(u);
            }

            template <typename ARR>
            static inline void OnBuildN(void *const  addr,
                                        void * const arg1,
                                        const size_t indx)
            {
                assert(0!=arg1);
                assert(indx>0);
                ARR &arr  = *static_cast<ARR*>(arg1);
                new (addr) MutableType(arr[indx]);
            }

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }
}

#endif // !Y_Memory_AutoBuilt_Included


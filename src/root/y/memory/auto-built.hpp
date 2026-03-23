//! \file

#ifndef Y_Memory_AutoBuilt_Included
#define Y_Memory_AutoBuilt_Included 1

#include "y/memory/auto-build.hpp"
#include "y/type/args.hpp"

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
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }
}

#endif // !Y_Memory_AutoBuilt_Included


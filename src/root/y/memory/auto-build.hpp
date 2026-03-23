
//! \file

#ifndef Y_Memory_AutoBuild_Included
#define Y_Memory_AutoBuild_Included 1

#include "y/type/destruct.hpp"
#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Auto construct/destruct memory areas with user's functions
        //
        //
        //______________________________________________________________________
        class AutoBuild
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef void (*Build0)(void * const);                             //!< default build
            typedef void (*Delete)(void * const);                             //!< destructor
            typedef void (*Build1)(void * const, void * const);               //!< build with argument
            typedef void (*BuildN)(void * const, void * const, const size_t); //!< procedural build

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with default constructor
            /**
             \param userBlockAddr base memory
             \param userNumBlocks blocks to create
             \param userBlockSize bytes per block
             \param userDeleteFcn destructor function
             \param userBuild0Fcn userBuild0Fcn(blockAddr) for each block
             */
            explicit AutoBuild(void * const userBlockAddr,
                               const size_t userNumBlocks,
                               const size_t userBlockSize,
                               Delete const userDeleteFcn,
                               Build0 const userBuild0Fcn);

            //! setup with one parameter constructor
            /**
             \param userBlockAddr base memory
             \param userNumBlocks blocks to create
             \param userBlockSize bytes per block
             \param userDeleteFcn destructor function
             \param userBuild1Fcn userBuild1Fcn(blockAddr,arg1) for each block
             \param arg1          argument
             */
            explicit AutoBuild(void * const userBlockAddr,
                               const size_t userNumBlocks,
                               const size_t userBlockSize,
                               Delete const userDeleteFcn,
                               Build1 const userBuild1Fcn,
                               void * const arg1);

            //! setup with one parameter constructor
            /**
             \param userBlockAddr base memory
             \param userNumBlocks blocks to create
             \param userBlockSize bytes per block
             \param userDeleteFcn destructor function
             \param userBuildNFcn userBuildNFcn(blockAddr,arg1,indx) for each block
             \param arg1          argument
             */
            explicit AutoBuild(void * const userBlockAddr,
                               const size_t userNumBlocks,
                               const size_t userBlockSize,
                               Delete const userDeleteFcn,
                               BuildN const userBuildNFcn,
                               void * const arg1);

            virtual ~AutoBuild() noexcept;

            void * const blockAddr; //!< base address
            const size_t numBlocks; //!< built blocks
            const size_t blockSize; //!< bytes per block
            Delete const deleteFcn; //!< destructor

        private:
            Y_Disable_Copy_And_Assign(AutoBuild); //!< discarded
            void deleteAll() noexcept;            //!< destruct all
        };

       
    }
}

#endif // !Y_Memory_AutoBuild_Included



#include "y/memory/auto-build.hpp"

namespace Yttrium
{
    namespace Memory
    {
        AutoBuild:: AutoBuild(void * const userBlockAddr,
                              const size_t userNumBlocks,
                              const size_t userBlockSize,
                              Delete const userDeleteFcn,
                              Build0 const userBuild0Fcn) :
        blockAddr(userBlockAddr),
        numBlocks(0),
        blockSize(userBlockSize),
        deleteFcn(userDeleteFcn)
        {
            assert(!(userBlockAddr==0&&userNumBlocks>0));
            assert(blockSize>0);
            assert(userDeleteFcn);
            assert(userBuild0Fcn);

            try {
                char * p = (char *)blockAddr;
                while(numBlocks<userNumBlocks)
                {
                    userBuild0Fcn(p);
                    p += blockSize;
                    ++Coerce(numBlocks);
                }
            }
            catch(...)
            {
                deleteAll();
                throw;
            }
        }


        AutoBuild:: AutoBuild(void * const userBlockAddr,
                              const size_t userNumBlocks,
                              const size_t userBlockSize,
                              Delete const userDeleteFcn,
                              Build1 const userBuild1Fcn,
                              void * const arg1) :
        blockAddr(userBlockAddr),
        numBlocks(0),
        blockSize(userBlockSize),
        deleteFcn(userDeleteFcn)
        {
            assert(!(userBlockAddr==0&&userNumBlocks>0));
            assert(blockSize>0);
            assert(userDeleteFcn);
            assert(userBuild1Fcn);

            
            try {
                char * p = (char *)blockAddr;
                while(numBlocks<userNumBlocks)
                {
                    userBuild1Fcn(p,arg1);
                    p += blockSize;
                    ++Coerce(numBlocks);
                }
            }
            catch(...)
            {
                deleteAll();
                throw;
            }
        }

        AutoBuild:: AutoBuild(void * const userBlockAddr,
                              const size_t userNumBlocks,
                              const size_t userBlockSize,
                              Delete const userDeleteFcn,
                              BuildN const userBuildNFcn,
                              void * const arg1) :
        blockAddr(userBlockAddr),
        numBlocks(0),
        blockSize(userBlockSize),
        deleteFcn(userDeleteFcn)
        {
            assert(!(userBlockAddr==0&&userNumBlocks>0));
            assert(blockSize>0);
            assert(userDeleteFcn);
            assert(userBuildNFcn);

            try {
                char * p = (char *)blockAddr;
                size_t i = 0;
                while(numBlocks<userNumBlocks)
                {
                    userBuildNFcn(p,arg1,++i);
                    p += blockSize;
                    ++Coerce(numBlocks);
                }
            }
            catch(...)
            {
                deleteAll();
                throw;
            }
        }



        void AutoBuild:: deleteAll() noexcept
        {
            assert(blockAddr);
            assert(blockSize>0);
            assert(deleteFcn!=0);
            char *   p = static_cast<char *>(blockAddr) + (numBlocks*blockSize);
            while(numBlocks>0)
            {
                --Coerce(numBlocks);
                deleteFcn(p -= blockSize);
            }
        }

        AutoBuild:: ~AutoBuild() noexcept
        {
            deleteAll();
        }
    }

}


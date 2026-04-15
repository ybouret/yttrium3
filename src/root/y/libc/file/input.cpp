
#include "y/libc/file/input.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include "y/string.hpp"
#include "y/format/decimal.hpp"

#include <cassert>
#include <cerrno>
#include <cstring>

namespace Yttrium
{
    namespace Libc
    {


        InputFile:: InputFile(const StdIn_ &) :
        File(stdin,false)
        {
            if(!handle) throw Libc::Exception(EIO,"no stdin!");
        }


        static inline
        FILE * OpenFileRO(const char * const fileName,
                          bool &             closeDown)
        {
            assert(fileName);
            
            if( 0 == strcmp(fileName,Y_STDIN) )
            {
                std::cerr << "STDIN!!" << std::endl;
                closeDown = false;
                if(!stdin) throw Libc::Exception(EIO,"no stdin!");
                return stdin;
            }

            Y_Giant_Lock();
            FILE * fp = fopen(fileName,"rb");
            if(!fp)
                throw Libc::Exception(errno,"fopen(%s)",fileName);
            closeDown = true;
            return fp;
        }

        InputFile:: InputFile(const char * const fileName) :
        File(0,true)
        {
            Coerce(handle) = OpenFileRO(fileName,Coerce(closeDown));
            if(closeDown) bufferize();
        }

        InputFile:: InputFile(const String &fileName) :
        File(0,true)
        {
            Coerce(handle) = OpenFileRO(fileName.c_str(),Coerce(closeDown));
            if(closeDown) bufferize();
        }


        InputFile:: ~InputFile() noexcept
        {
        }

        bool InputFile:: query(char &C)
        {
            static const char fn[] = "fread";
            Y_Giant_Lock();
            if( feof(handle) )
                return false;

            if( fread(&C,1,1,handle) <= 0)
            {
                if(feof(handle))
                    return false;
                
                if( !ferror(handle) )
                    throw Specific::Exception(fn,"undefined error");

                throw Libc::Exception(errno,"%s(1)",fn);
            }

            return true;
        }


        size_t InputFile:: query(void * const blockAddr, const size_t blockSize)
        {
            static const char fn[] = "fread";
            assert(0!=blockAddr);
            assert(blockSize>0);
            Y_Giant_Lock();
            const size_t numRead = fread(blockAddr, 1, blockSize, handle);
            if(numRead<blockSize)
            {
                if( feof(handle) ) return numRead;
                
                if( !ferror(handle) )
                    throw Specific::Exception(fn,"undefined error");

                throw Libc::Exception(errno,"%s(%s)",fn,Decimal(blockSize).c_str());
            }

            return numRead;
        }


    }

}



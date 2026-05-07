
#if defined(_MSC_VER)
#pragma warning ( disable : 4668 )
#endif

#include "y/stream/gz/output.hpp"
#include "y/ability/lockable.hpp"
#include "y/zlib/zlib.h"
#include "y/exception.hpp"
#include "y/core/clamp.hpp"
#include "y/core/min.hpp"

namespace Yttrium
{
    namespace GZ
    {
        namespace
        {
            static const char * OpenMode[10] =
            {
                "w0",
                "w1",
                "w2",
                "w3",
                "w4",
                "w5",
                "w6",
                "w7",
                "w8",
                "w9"
            };
        }

        const char * Output:: GetMode(const int level) noexcept
        {
            return OpenMode[ Clamp<int>(0,level,9) ];
        }

        Output:: ~Output() noexcept
        {
            
        }

        void Output:: write(const char c)
        {
            assert(handle);
            Y_Giant_Lock();
            gzFile const fp  = static_cast<gzFile>(handle);
            if( gzwrite(fp,&c,1) <= 0)
            {
                int                err = 0;
                const char * const txt = gzerror(fp,&err);
                throw Specific::Exception("gzWrite(1)", "%s",txt);
            }
        }

        void Output:: write(const void * const addr, const size_t size)
        {
            static const size_t MaxBlockSize = IntegerFor<int>::Maximum;
            assert(handle);
            assert( !(0==addr&&size>0) );
            Y_Giant_Lock();
            gzFile const    fp        = static_cast<gzFile>(handle);
            size_t          remaining = size;
            const uint8_t * blockAddr = static_cast<const uint8_t *>(addr);
            while(remaining>0)
            {
                const size_t blockSize = Min(remaining,MaxBlockSize);
                const int    res       = gzwrite(fp,blockAddr,(unsigned)blockSize);
                if(res < (int) blockSize )
                {
                    int                err = 0;
                    const char * const txt = gzerror(fp,&err);
                    throw Specific::Exception("gzWrite(block)", "%s",txt);
                }
                remaining -= blockSize;
                blockAddr += blockSize;
            }
        }

        void Output:: flush()
        {
            assert(handle);
            Y_Giant_Lock();
            gzFile const fp  = static_cast<gzFile>(handle);
            const int    res = gzflush(fp,Z_FINISH);
            if(Z_OK!=res)
            {
                throw Specific::Exception("gzFlush", "flush failure");
            }
        }


    }

}


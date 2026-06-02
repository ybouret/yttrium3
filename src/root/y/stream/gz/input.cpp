#if defined(_MSC_VER)
#pragma warning ( disable : 4668 )
#endif

#include "y/stream/gz/input.hpp"
#include "y/ability/lockable.hpp"
#include "y/zlib/zlib.h"
#include "y/exception.hpp"
#include "y/core/min.hpp"

namespace Yttrium
{
    namespace GZ
    {

        const char * const Input:: Mode = "r";
        
        Input:: ~Input() noexcept
        {
        }

        void Input:: store(const char c)
        {
            buff >> c;
        }

        bool Input:: query(char &c)
        {
            assert(handle);

            if(buff.size)
            {
                c = **buff.head;
                delete buff.popHead();
                return true;
            }
            else
            {
                gzFile const fp = static_cast<gzFile>(handle);
                Y_Giant_Lock();
                if( gzread(fp,&c,1) <= 0 )
                {
                    if(gzeof(fp))
                    {
                        return false;
                    }

                    int                err = 0;
                    const char * const txt = gzerror(fp,&err);
                    throw Specific::Exception(title->c_str(),"%s",txt);
                }
                else
                    return true;
            }
        }

        namespace {

            static inline size_t transfer(void * const  data,
                                          IO::Chars   & buff,
                                          const size_t  size) noexcept
            {
                assert(size<=buff.size);
                char * p = (char *)data;
                for(size_t n=size;n>0;--n)
                {
                    *(p++) =  buff.pullHead();
                }
                return size;
            }
        }

        size_t Input:: query(void * const addr, const size_t size)
        {
            static const size_t MaxSize = (size_t)IntegerFor<int>::Maximum;
            assert(!(addr==0&&size>0));

            if( size <= buff.size )
            {
                return transfer(addr,buff,size);
            }
            else
            {
                const size_t    loaded = transfer(addr,buff,buff.size);
                const size_t    count  = Min(size-loaded,MaxSize); assert(count>0);
                uint8_t * const entry  = static_cast<uint8_t*>(addr) + loaded;
                gzFile const    fp     = static_cast<gzFile>(handle);
                Y_Giant_Lock();
                const int       numRead = gzread(fp,entry,(unsigned)count);
                if(numRead<(int)count && !gzeof(fp) )
                {
                    int                err = 0;
                    const char * const txt = gzerror(fp,&err);
                    throw Specific::Exception(title->c_str(),"%s",txt);
                }
                return loaded + numRead;
            }


        }

    }

}

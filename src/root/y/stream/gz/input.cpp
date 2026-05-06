#include "y/stream/gz/input.hpp"
#include "y/ability/lockable.hpp"
#include <zlib.h>

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
                gzFile fp = static_cast<gzFile>(handle);
                Y_Giant_Lock();
                if( gzread(fp,&c,1) <= 0 )
                {
                    if(gzeof(fp))
                    {
                        return false;
                    }

                    int                err = 0;
                    const char * const txt = gzerror(fp,&err);

                }
                else
                    return true;
            }
        }

    }

}


#include "y/stream/input.hpp"

namespace Yttrium
{

    InputStream::  InputStream() : Stream() {}
    InputStream:: ~InputStream() noexcept {}

    bool InputStream:: peek(char &C)
    {
        if( query(C) )
        {
            store(C);
            return true;
        }
        else
            return false;
    }

    bool InputStream:: gets(String &s)
    {
        s.free();

    GETCHAR:
        {
            char c = 0;
            if(!query(c))
                return s.size()>0;

            switch(c)
            {

                case CR:
                    if(query(c)) {
                        if(LF!=c)
                            store(c);
                    }
                    return true;
                    
                case LF: return true;
                default: break;

            }
            s += c;
            goto GETCHAR;
        }



        return false;
    }

}

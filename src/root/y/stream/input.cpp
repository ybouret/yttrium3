
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
            char C = 0;
            if(!query(C))
                return s.size()>0;

            switch(C)
            {


                case LF: return true;
                default: break;

            }
            s += C;
            goto GETCHAR;
        }



        return false;
    }

}

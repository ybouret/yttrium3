#include "y/chemical/library.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Library:: ~Library() noexcept
        {
        }

        Y_Proxy_Impl(Library,db)

        const char * const Library:: CallSign = "Library";

        Library:: Library() : db()
        {
        }

        Species & Library:: operator[](const Formula &f)
        {
            int           z    = 0;
            const String  name = f.makeName(&z);
            SpPtr * const ppS  = db.search(name);
            if(ppS)
            {
                Species &sp = **ppS; assert(sp.z == z);
                return sp;
            }
            else
            {
                if(frozen)
                    throw Specific::Exception(CallSign,"canot append '%s' to frozen library", name.c_str());

                SpPtr pS( new Species(f,db.size()+1) );

                if(!db.insert(pS))
                    throw Specific::Exception(CallSign,"unable to insert new species '%s'", name.c_str());

                return *pS;
            }
        }


    }

}


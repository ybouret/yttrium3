#include "y/chemical/library.hpp"
#include "y/exception.hpp"
#include <iomanip>
#include "y/core/display.hpp"

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
            SpPtr         pS( new Species(f,db.size()+1) );
            const String &name = pS->name;

            {
                SpPtr *ppS = db.search(name);
                if(ppS)
                {
                    assert(pS->z==(**ppS).z);
                    return **ppS;
                }
            }

            if(frozen)
                throw Specific::Exception(CallSign,"canot append '%s' to frozen library", name.c_str());

            if(!db.insert(pS))
                throw Specific::Exception(CallSign,"unable to insert new species '%s'", name.c_str());

            enroll(*pS);
            return *pS;
        }

        std::ostream & operator<<(std::ostream &os, const Library &lib)
        {
            os << '{' << std::endl;
            for(Library::ConstIterator it=lib->begin();it!=lib->end();++it)
            {
                const Species &sp = **it;
                lib.print(std::cerr << "\t",sp) << " | z = " << std::setw(3) << sp.z;
                Core::Display(std::cerr << " | ",sp.indx,sp.Levels) << std::endl;
            }
            return os << '}';
        }


    }

}


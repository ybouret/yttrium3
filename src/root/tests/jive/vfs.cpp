#include "y/jive/vfs.hpp"
#include "y/vfs/local/fs.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(jive_vfs)
{
    if(argc>1)
    {
        const char * const rxExt = argv[1];
        Jive::_VFS::OnExtension( LocalFS::Instance(), ".", rxExt, Jive::_VFS::Display);
    }
}
Y_UDONE()


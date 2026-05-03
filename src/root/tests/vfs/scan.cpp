#include "y/vfs/local/fs.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;

Y_UTEST(vfs_scan)
{
    VFS &                 fs = LocalFS::Instance();
    const String          dir = argc > 1 ? argv[1] : ".";
    AutoPtr<VFS::Scanner> scan = fs.openDirectory(dir);
    
}
Y_UDONE()


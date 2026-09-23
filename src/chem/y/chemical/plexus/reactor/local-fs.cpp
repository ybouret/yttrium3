
#include "y/chemical/plexus/reactor.hpp"
#include "y/vfs/local/fs.hpp"
#include "y/jive/vfs.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        void Reactor:: TryRemoveProfiles(const String &dirName)
        {
            Jive::_VFS::Apply( LocalFS::Instance(), dirName, StdProfileExt, Jive::Matching::Exactly, VFS::Entry::Ext, Jive::_VFS::Remove);
            Jive::_VFS::Apply( LocalFS::Instance(), dirName, OptProfileExt, Jive::Matching::Exactly, VFS::Entry::Ext, Jive::_VFS::Remove);
        }

        void Reactor:: TryRemoveRunStats(const String &dirName)
        {
            Jive::_VFS::Apply( LocalFS::Instance(), dirName, "solver[:digit:]+[.]dat", Jive::Matching::Exactly, VFS::Entry::Base, Jive::_VFS::Remove);
        }
    }

}


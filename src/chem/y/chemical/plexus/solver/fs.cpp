#include "y/chemical/plexus/solver.hpp"
#include "y/jive/vfs.hpp"
#include "y/vfs/local/fs.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        void Solver:: TryRemoveProfiles(const String & dirName, const char * const profileExt)
        {
            assert(profileExt);
            Jive::_VFS::Apply( LocalFS::Instance(), dirName, profileExt, Jive::Matching::Exactly, VFS::Entry::Ext, Jive::_VFS::Remove);
        }

        void Solver:: TryRemoveRunStats(const String &dirName)
        {
            Jive::_VFS::Apply( LocalFS::Instance(), dirName, "solver[:digit:]+[.]dat", Jive::Matching::Exactly, VFS::Entry::Base, Jive::_VFS::Remove);
        }

    }
}


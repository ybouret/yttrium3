//! \file

#ifndef Y_Handy_DirectCache_Included
#define Y_Handy_DirectCache_Included 1

#include "y/handy/cache/defs.hpp"

namespace Yttrium
{
    namespace Handy
    {
        template <typename NODE, typename THREADING_POLICY>
        class DirectCache : public THREADING_POLICY
        {
        public:
            Y_HandyCache_Decl();

            inline explicit DirectCache() : ThreadingPolicy()
            {

            }

            inline virtual ~DirectCache() noexcept
            {
            }


            inline NodeType * summon(ParamType args) {
                Y_Must_Lock();
                NodeType * const node = LightObject::AcquireZombie<NodeType>();
                try {
                    return new (node) NodeType(args);
                }
                catch(...) {
                    LightObject::ReleaseZombie( NodeAPI::Clear(node) );
                    throw;
                }
            }

            inline void banish(NodeType * const alive) noexcept
            {
                Y_Must_Lock();
                assert(alive);
                LightObject::ReleaseZombie( Pulverized(alive) );
            }

            inline void remove(NodeType * const alive) noexcept
            {
                banish(alive);
            }



        private:
            Y_Disable_Copy_And_Assign(DirectCache);
        };
    }

}


#endif // !Y_Handy_DirectCache_Included


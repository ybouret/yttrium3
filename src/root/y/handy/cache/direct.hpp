//! \file

#ifndef Y_Handy_DirectCache_Included
#define Y_Handy_DirectCache_Included 1

#include "y/handy/cache/defs.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    
    namespace Handy
    {
        //______________________________________________________________________
        //
        //
        //
        //! Direct communication to light objects
        //
        //
        //______________________________________________________________________
        template <typename NODE, typename THREADING_POLICY>
        class DirectCache : public THREADING_POLICY
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_HandyCache_Decl(); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit DirectCache() : ThreadingPolicy() {} //!< setup
            inline virtual ~DirectCache() noexcept            {} //!< cleanup

            //! duplicate
            inline DirectCache(const DirectCache &) : ThreadingPolicy() {}


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! summon new node
            /**
             \param args for constructor
             \return constructed node
             */
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

            //! mirror existing node
            /**
             \param mine for copy constructor
             \return duplicate node
             */
            inline NodeType * mirror(const NodeType * const mine)
            {
                assert(mine);
                Y_Must_Lock();
                NodeType * const node = LightObject::AcquireZombie<NodeType>();
                try {
                    return new (node) NodeType(*mine);
                }
                catch(...) {
                    LightObject::ReleaseZombie( NodeAPI::Clear(node) );
                    throw;
                }
            }


            //! banish living node \param alive live node
            inline void banish(NodeType * const alive) noexcept
            {
                Y_Must_Lock();
                assert(alive);
                LightObject::ReleaseZombie( Pulverized(alive) );
            }


            //! remove living node \param alive live node
            inline void removeLiving(NodeType * const alive) noexcept
            {
                banish(alive);
            }

            //! remove zombie node \param zombie zombie node
            inline void removeZombie(NodeType * const zombie) noexcept
            {
                Y_Must_Lock();
                assert(zombie);
                LightObject::ReleaseZombie(zombie);
            }

            

            inline DirectCache *       operator->()       noexcept { return this;  } //!< \return API
            inline const DirectCache * operator->() const noexcept { return this;  } //!< \return API
            inline Lockable &          operator*()        noexcept { return *this; } //!< \return lockable



        private:
            Y_Disable_Assign(DirectCache); //!< discarded
        };
    }

}


#endif // !Y_Handy_DirectCache_Included


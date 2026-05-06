
//! \file

#ifndef Y_Core_Tree_Pool_Included
#define Y_Core_Tree_Pool_Included 1

#include "y/core/tree/node.hpp"
#include "y/core/pool/cxx.hpp"
#include "y/ability/caching.hpp"

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! Cache of TreeNodes
        //
        //
        //______________________________________________________________________
        class TreePool : public CxxPoolOf<TreeNode>, public Caching
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit TreePool() noexcept; //!< setup
            virtual ~TreePool() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t count() const noexcept;
            virtual void   cache(const size_t);
            virtual void   gc(const uint8_t) noexcept;

        private:
            Y_Disable_Copy_And_Assign(TreePool); //!< discarded
        };
    }

}

#endif // !Y_Core_Tree_Pool_Included


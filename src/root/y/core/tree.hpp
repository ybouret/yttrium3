
//! \file

#ifndef Y_Core_Tree_Included
#define Y_Core_Tree_Included 1

#include "y/core/tree/node.hpp"
#include "y/core/pool/cxx.hpp"

namespace Yttrium
{
    namespace Core
    {
        typedef CxxPoolOf<TreeNode> TreePool;

        class Tree
        {
        public:
            explicit Tree();
            virtual ~Tree() noexcept;

            //! search path with move to head optimization
            /**
             \return node existence along path (with any args)
             */
            TreeNode * search(const void * const path,
                              size_t             plen) noexcept;



            //!
            /**
             \return node existence along path (with any args)
             */
            const TreeNode * search(const void * const path,
                                    size_t             plen) const noexcept;

            //!
            /**
             \param args args != NULL
             \return true if coudl find/create node and set its data
             */
            bool insert(const void * const path,
                        size_t             plen,
                        void * const       args);


            bool insert(const char * const path, void * const args);

            OutputStream & viz(OutputStream &fp) const;

        private:
            TreeNode * const root; //!< root for 0-length path
            TreePool         pool; //!< cache of nodes

            TreeNode * queryNode(const uint8_t, void * const);

        };










    }

}

#endif // !Y_Core_Tree_Included


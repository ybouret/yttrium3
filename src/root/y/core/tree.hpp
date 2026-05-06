
//! \file

#ifndef Y_Core_Tree_Included
#define Y_Core_Tree_Included 1

#include "y/core/tree/node.hpp"
#include "y/core/pool/cxx.hpp"

namespace Yttrium
{
    namespace Core
    {
        typedef CxxPoolOf<TreeNode> TreePool; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Anonymous suffix tree
        //
        //
        //______________________________________________________________________
        class Tree
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Tree();          //!< setup with empty root
            virtual ~Tree() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Search Methods
            //
            //__________________________________________________________________

            //! search path with move to head optimization
            /**
             \param path anonymous path
             \param plen path length
             \return node existence along path (empty or not!)
             */
            TreeNode * search(const void * const path,
                              size_t             plen) noexcept;

            //! search path without optimization
            /**
             \param path anonymous path
             \param plen path length
             \return node existence along path (empty or not!)
             */
            const TreeNode * search(const void * const path,
                                    size_t             plen) const noexcept;


            //__________________________________________________________________
            //
            //
            // Insert Methods
            //
            //__________________________________________________________________

            //! insert data at given path
            /**
             \param path anonymous path
             \param plen path length
             \param args args != NULL
             \return true if could find/create node and set its data
             */
            bool insert(const void * const path,
                        size_t             plen,
                        void * const       args);

            //! insert wrapper for text \return true iff inserted at given path
            bool insert(const char * const, void * const);


            //__________________________________________________________________
            //
            //
            // Remove Methods
            //
            //__________________________________________________________________
            void * remove(const void * const path, const size_t plen) noexcept;
            void * remove(const char * const) noexcept;

            //__________________________________________________________________
            //
            //
            // Other Methods
            //
            //__________________________________________________________________
            OutputStream & viz(OutputStream &) const; //!< emit GraphViz \return output stream

        private:
            Y_Disable_Copy_And_Assign(Tree); //!< discarded
            TreeNode * const root;           //!< root for 0-length path
        public:
            const size_t     size;           //!< current inserted data count
            TreePool         pool;           //!< cache of nodes

            //! \return pooled/created node with code and data
            TreeNode * queryNode(const uint8_t, void * const, TreeNode * const);

            void prune(TreeNode * const) noexcept;


        };










    }

}

#endif // !Y_Core_Tree_Included


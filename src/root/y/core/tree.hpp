
//! \file

#ifndef Y_Core_Tree_Included
#define Y_Core_Tree_Included 1

#include "y/core/tree/pool.hpp"
#include "y/ability/recyclable.hpp"

namespace Yttrium
{
    namespace Memory { class ReadOnlyBuffer; }

    namespace Core
    {

        //______________________________________________________________________
        //
        //
        //
        //! Anonymous suffix tree
        //
        //
        //______________________________________________________________________
        class Tree : public Recyclable, public Releasable
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



            //__________________________________________________________________
            //
            //
            // Remove Methods
            //
            //__________________________________________________________________

            //! remove content and prune a valid node
            /**
             \param path anonymous path
             \param plen path length
             \return   data from existing, occupied node
             */
            void * remove(const void * const path, const size_t plen) noexcept;

            //__________________________________________________________________
            //
            //
            // Other Methods
            //
            //__________________________________________________________________
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            TreeNode *       search(const char * const)                   noexcept;
            TreeNode *       search(const Memory::ReadOnlyBuffer &)       noexcept;
            const TreeNode * search(const char * const)             const noexcept;
            const TreeNode * search(const Memory::ReadOnlyBuffer &) const noexcept;
            void *           remove(const char * const)                   noexcept;
            void *           remove(const Memory::ReadOnlyBuffer &)       noexcept;
            bool             insert(const char * const, void * const);
            bool             insert(const Memory::ReadOnlyBuffer &, void * const);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            virtual void free()    noexcept;
            virtual void release() noexcept;

            OutputStream & viz(OutputStream &) const; //!< emit GraphViz \return output stream

        private:
            Y_Disable_Copy_And_Assign(Tree); //!< discarded
            TreeNode * const root;           //!< root for 0-length path
        public:
            const size_t     size;           //!< current inserted data count
            TreePool         pool;           //!< cache of nodes

            //! \return pooled/created node with code and data
            TreeNode * queryNode(const uint8_t, void * const, TreeNode * const);

            //! prune node, returning to pool
            void prune(TreeNode *) noexcept;

            void free(TreeNode * const) noexcept;
        };

        
    }

}

#endif // !Y_Core_Tree_Included


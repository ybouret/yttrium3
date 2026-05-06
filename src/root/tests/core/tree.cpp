#include "y/core/list/cxx.hpp"
#include "y/core/pool/cxx.hpp"
#include "y/graphviz/vizible.hpp"

#include "y/object.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Core
    {
        class   TreeNode;
        typedef CxxListOf<TreeNode> TreeList;
        typedef CxxPoolOf<TreeNode> TreePool;

        class TreeNode : public Object, public Vizible
        {
        public:
            explicit TreeNode(const uint8_t c, void * const d) noexcept :
            Object(), code(c), data(d), list(), next(0), prev(0)
            {
            }

            virtual ~TreeNode() noexcept {}

            TreeNode * erased() noexcept
            {
                Coerce(code) = 0;
                Coerce(data) = 0;
                return this;
            }

            const uint8_t code;
            void * const  data;
            TreeList      list;
            TreeNode *    next;
            TreeNode *    prev;

        private:
            Y_Disable_Copy_And_Assign(TreeNode);
        };

        class Tree
        {
        public:
            explicit Tree();
            virtual ~Tree() noexcept;

            //!
            /**
             \return node existence along path (with any args)
             */
            TreeNode * search(const void * const path,
                              size_t             plen) noexcept;


            //!
            /**
             \param args args != NULL
             \return true if coudl find/create node and set its data
             */
            bool insert(const void * const path,
                        size_t             plen,
                        void * const       args);



        private:
            TreeNode * const root;
            TreePool         pool;

            TreeNode * queryNode(const uint8_t, void * const);

        };

        Tree:: Tree() : root( new TreeNode(0,0) )
        {
        }

        Tree:: ~Tree() noexcept
        {
            Destroy(root);
        }

        TreeNode * Tree:: queryNode(const uint8_t code, void * const data)
        {
            if(pool.size)
            {
                TreeNode * const node = pool.query();
                Coerce(node->code) = code;
                Coerce(node->data) = data;
                return node;
            }
            else
            {
                return new TreeNode(code,data);
            }
        }


        TreeNode * Tree:: search(const void * const path,
                                 size_t             plen) noexcept
        {
            assert(!(path==0&&plen>0));
            assert(0!=root);
            TreeNode *       node = root;
            const uint8_t  * kptr = static_cast<const uint8_t *>(path);
            while(plen-- > 0)
            {
                const uint8_t code = *(kptr++);
                bool          walk = false;
                TreeList &    list = node->list;
                for(TreeNode * scan=list.head;scan;scan=scan->next)
                {
                    if(code==scan->code) {
                        node = list.moveToHead(scan);;
                        walk = true;
                        break;
                    }
                }
                if(!walk) return 0;
            }
            return node;
        }

        bool Tree:: insert(const void * const path,
                    size_t             plen,
                    void * const       args)
        {
            assert(!(path==0&&plen>0));
            assert(0!=root);
            assert(0!=args);
            TreeNode *       node = root;
            const uint8_t  * kptr = static_cast<const uint8_t *>(path);
            while(plen-- > 0)
            {
                const uint8_t code = *(kptr++);
                bool          walk = false;
                TreeList &    list = node->list;
                for(TreeNode * scan=list.head;scan;scan=scan->next)
                {
                    if(code==scan->code) {
                        node = list.moveToHead(scan);;
                        walk = true;
                        break;
                    }
                }
                if(!walk)
                    node = list.pushHead( queryNode(code,0) );
            }

            if(node->data)
            {
                return false;
            }
            else
            {
                Coerce(node->data) = args;
                return true;
            }
        }

    }
}

#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(core_tree)
{

    Y_SIZEOF(Core::TreeNode);

    Core::Tree tree;

}
Y_UDONE()


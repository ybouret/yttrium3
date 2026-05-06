#include "y/core/tree.hpp"
#include "y/type/destroy.hpp"
#include "y/string/length.hpp"

namespace Yttrium
{
    namespace Core
    {
        Tree:: ~Tree() noexcept
        {
            Destroy(root);
        }

        Tree:: Tree() :
        root( new TreeNode(0,0) ),
        size(0),
        pool()
        {
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
                        node = list.moveToHead(scan);
                        walk = true;
                        break;
                    }
                }
                if(!walk) return 0;
            }
            return node;
        }

        const TreeNode * Tree:: search(const void * const path,
                                       size_t             plen) const noexcept
        {
            assert(!(path==0&&plen>0));
            assert(0!=root);
            const TreeNode * node = root;
            const uint8_t  * kptr = static_cast<const uint8_t *>(path);
            while(plen-- > 0)
            {
                const uint8_t    code = *(kptr++);
                bool             walk = false;
                const TreeList & list = node->list;
                for(TreeNode * scan=list.head;scan;scan=scan->next)
                {
                    if(code==scan->code) {
                        node = scan;
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
                return false; // already occupied
            }
            else
            {
                Coerce(node->data) = args;
                ++Coerce(size);
                return true;
            }
        }

        bool Tree:: insert(const char * const path, void * const args)
        {
            return insert(path,StringLength(path),args);
        }

        OutputStream & Tree:: viz(OutputStream &fp) const
        {
            assert(root);
            return root->viz(fp);
        }

        void * Tree:: remove(const void * const path, size_t plen) noexcept
        {
            TreeNode * const node = search(path,plen); assert(node);
            void *     const args = node->data;        assert(args);
            Coerce(node->data) = 0;

            --Coerce(size);
            return args;
        }

        void * Tree:: remove(const char * const path) noexcept
        {
            return remove(path,StringLength(path));
        }


    }
}

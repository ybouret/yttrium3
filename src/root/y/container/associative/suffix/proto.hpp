
//! \file

#ifndef Y_Associative_SuffixProto_Inluded
#define Y_Associative_SuffixProto_Inluded 1

#include "y/container/associative.hpp"
#include "y/core/tree.hpp"

namespace Yttrium
{

    template <
    typename KEY,
    typename T,
    template <typename, typename> class NODE >
    class SuffixProto : public Associative<KEY, T>
    {
    public:
        typedef NODE<KEY, T>       Node;
        typedef Core::ListOf<Node> List; //!< alive nodes
        typedef Core::ListOf<Node> Pool; //!< zombi nodes

        inline explicit SuffixProto() : list(), tree(), pool()
        {
        }
        

        inline virtual ~SuffixProto() noexcept {}

        inline virtual size_t size()     const noexcept { return list.size; }
        inline virtual size_t capacity() const noexcept { return list.size+pool.size; }

    protected:
        List       list;
        Core::Tree tree;
        Pool       pool;

    private:
        Y_Disable_Assign(SuffixProto);
        Y_Disable_Copy(SuffixProto);




    };

}

#endif // !Y_Associative_SuffixProto_Inluded


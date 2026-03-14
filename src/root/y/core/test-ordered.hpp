//! \file

#ifndef Y_Core_Test_Ordered_Included
#define Y_Core_Test_Ordered_Included

namespace Yttrium
{
    namespace Core
    {
        //! helper to test ordered collection
        struct TestOrdered
        {
            //! test array
            /**
             \param arr array entry
             \param num number of elements
             \param compare comparison
             \param verify  stricty/loosely
             \return true iff ordered
             */
            template <typename T, typename COMPARE, typename VERIFY> static inline
            bool Array(const T arr[], const size_t num, COMPARE &compare, VERIFY &verify)
            {
                if(num<=1) return true;
                const size_t top = num-1;
                for(size_t i=0;i<top;++i)
                {
                    if( !verify(compare(arr[i],arr[i+1]) ) ) return false;
                }
                return true;
            }

            //! test linked
            /**
             \param linked       with head node and size
             \param compareNodes node comparison
             \param verify       stricty/loosely
             \return true iff ordered
             */
            template <typename LINKED, typename COMPARE_NODES, typename VERIFY> static inline
            bool Linked(LINKED &linked, COMPARE_NODES &compareNodes, VERIFY &verify)
            {
                const size_t num = linked.size;
                if(num<=1) return true;
                const typename LINKED::NodeType *curr = linked.head, *next=curr->next;
                for(size_t i=num-1;i>0;--i)
                {
                    assert(curr);
                    assert(next);
                    if(!verify(compareNodes(curr,next))) return false;
                    curr=next;
                    next=next->next;
                }
                return true;
            }



        };
    }
}

#endif // !Y_Core_Test_Ordered_Included


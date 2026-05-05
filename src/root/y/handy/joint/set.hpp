
//! \file

#ifndef Y_Handy_JointSet_Included
#define Y_Handy_JointSet_Included 1

#include "y/handy/joint/heavy/list.hpp"
#include "y/type/sign.hpp"


namespace Yttrium
{
    namespace Handy
    {
        template <
        typename T,
        typename THREAD_POLICY,
        typename COMPARATOR = Sign::Comparator<T> >
        class  JointSet : public Proxy<const JointHeavyList<T,THREAD_POLICY> >
        {
        public:
            typedef JointHeavyList<T,THREAD_POLICY> ListType;
            typedef typename ListType::CacheType    CacheType;
            typedef Proxy<const ListType>           ProxyType;
            typedef typename ListType::NodeType     NodeType;
            typedef typename ListType::CoreList     CoreList;
            Y_Args_Declare(T,Type);

            inline explicit JointSet(const CacheType &sc) :
            ProxyType(),
            list(sc),
            compare()
            {
            }

            inline JointSet(const JointSet &other) :
            ProxyType(),
            list(other.list),
            compare()
            {
            }

            inline virtual ~JointSet() noexcept
            {
            }

            JointSet & operator<<(ParamType args)
            {
                assert( !list.found(args) );
                list << args;
                update();
                return *this;
            }

            JointSet & insert(NodeType * const node)
            {
                assert(node);
                assert(!list.found(**node));
                list->pushTail(node);
                update();
                return *this;
            }

            inline friend bool operator==(const JointSet &lhs, const JointSet &rhs)
            {
                return ListType::AreIdentical(lhs.list,rhs.list);
            }

            inline friend bool operator!=(const JointSet &lhs, const JointSet &rhs)
            {
                return !ListType::AreIdentical(lhs.list,rhs.list);
            }





        private:
            Y_Disable_Assign(JointSet);
            ListType   list;
            COMPARATOR compare;
            virtual typename ProxyType::ConstInterface & locus() const noexcept { return list; }
            inline void update()
            {
                CoreList &core = *list;
                assert(core.size>0);
                assert(core.tail);
                NodeType * node = core.tail;
                while(node->prev && Negative != compare(**(node->prev),**node) )
                    core.towardsHead(node);

            }
        };

    }

}

#endif // !Y_Handy_JointSet_Included

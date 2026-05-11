
//! \file

#ifndef Y_Handy_JointSet_Included
#define Y_Handy_JointSet_Included 1

#include "y/handy/joint/heavy/list.hpp"
#include "y/type/sign.hpp"


namespace Yttrium
{
    namespace Handy
    {
        //______________________________________________________________________
        //
        //
        //
        //! set of unique data with shared cache
        //
        //
        //______________________________________________________________________
        template <
        typename T,
        typename THREAD_POLICY,
        typename COMPARATOR = Sign::Comparator<T> >
        class  JointSet :
        public Proxy<const JointHeavyList<T,THREAD_POLICY> >,
        public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef JointHeavyList<T,THREAD_POLICY> ListType;  //!< alias
            typedef typename ListType::CacheType    CacheType; //!< alias
            typedef Proxy<const ListType>           ProxyType; //!< alias
            typedef typename ListType::NodeType     NodeType;  //!< alias
            typedef typename ListType::CoreList     CoreList;  //!< alias
            Y_Args_Declare(T,Type);                            //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param sc shared cache
            inline explicit JointSet(const CacheType &sc) :
            ProxyType(),
            Recyclable(),
            list(sc),
            compare()
            {
            }

            //! duplicate \param other another set
            inline JointSet(const JointSet &other) :
            ProxyType(),
            Recyclable(),
            list(other.list),
            compare()
            {
            }

            //! cleanup
            inline virtual ~JointSet() noexcept
            {
            }



            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! insert NON-EXISTING data
            /**
             \param args data
             \return *this*
             */
            JointSet & operator<<(ParamType args)
            {
                assert( !list.found(args) );
                list << args;
                update();
                return *this;
            }

            //! insert node with NON-EXISTING data
            /**
             \param node valid node
             \return *this
             */
            JointSet & insert(NodeType * const node)
            {
                assert(node);
                assert(!list.found(**node));
                Y_Lock(list);
                list->pushTail(node);
                update();
                return *this;
            }

            //! \param i node index in [1:size] \return extracted i-th node
            inline NodeType * extract(const size_t i) noexcept
            {
                return list->pop( list->fetch(i) );
            }

            inline NodeType * popHead() noexcept
            {
                return list->popHead();
            }

            inline NodeType * popTail() noexcept
            {
                return list->popTail();
            }

            
            //! \param i node index in [1:size] \return data at i-th node
            inline ConstType & operator[](const size_t i) const noexcept
            {
                return ** list->fetch(i);
            }


            //! \param value value to remove \return found node with given value, null otherwise
            inline NodeType * remove(ParamType value) noexcept
            {
                for(NodeType *node=list->head;node;node=node->next)
                {
                    if(value == **node) return list->pop(node);
                }
                return 0;
            }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            inline friend bool operator==(const JointSet &lhs, const JointSet &rhs)
            {
                return ListType::AreIdentical(lhs.list,rhs.list);
            }

            inline friend bool operator!=(const JointSet &lhs, const JointSet &rhs)
            {
                return !ListType::AreIdentical(lhs.list,rhs.list);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)


            inline virtual void free() noexcept { list.free(); }

            //! check if rhs is included within this
            /**
             \todo optimize
             \param rhs another set
             \return true iff each rhs item is found within this
             */
            inline bool contains(const JointSet &rhs) const noexcept
            {
                if(rhs.list->size>list->size) return false;
                for(const NodeType *node=rhs.list->head;node;node=node->next)
                {
                    if(!list.found(**node)) return false;
                }
                return true;
            }


            //! optimized search \param value value to look for \return true iff found value
            inline bool contains(ParamType value) const noexcept
            {

                switch(list->size)
                {
                    case 0: return false;
                    case 1: return value == **list->head;
                    case 2: return value == **list->head || value == **list->tail;
                    default:
                        break;
                }
                assert(list->size>=3);

                switch(compare(value,**list->head))
                {
                    case Negative: return false;
                    case __Zero__: return true;
                    case Positive: break;
                }

                switch(compare(value,**list->tail))
                {
                    case Positive: return false;
                    case __Zero__: return true;
                    case Negative: break;
                }

                for(const NodeType *node=list->head->next;node!=list->tail;node=node->next)
                {
                    // TODO: break at one point
                    switch(compare(value,**node))
                    {
                        case __Zero__: return true;
                        case Positive:
                        case Negative:
                            continue;
                    }
                }

                return false;
            }



        private:
            Y_Disable_Assign(JointSet); //!< discarded
            ListType   list;            //!< content
            COMPARATOR compare;         //!< comparator
            virtual typename ProxyType::ConstInterface & locus() const noexcept { return list; }

            //! put tail node in its position
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

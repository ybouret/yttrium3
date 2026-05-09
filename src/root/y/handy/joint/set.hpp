
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
        public Proxy<const JointHeavyList<T,THREAD_POLICY> >
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
            list(sc),
            compare()
            {
            }

            //! duplicate \param other another set
            inline JointSet(const JointSet &other) :
            ProxyType(),
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

            inline NodeType * extract(const size_t i) noexcept
            {
                return list->pop( list->fetch(i) );
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

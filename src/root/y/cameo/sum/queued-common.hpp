
//! \file

#ifndef Y_Cameo_Sum_Queued_Common
#define Y_Cameo_Sum_Queued_Common 1

#include "y/cameo/sum/api/queued.hpp"
#include "y/cameo/summator.hpp"
#include "y/mkl/api/fabs.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum
        {

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename T>
            class QAdd
            {
            public:
                Y_Args_Declare(T,Type);

                inline  QAdd(ParamType value) noexcept : data(value), rank(MKL::Fabs<MutableType>(data)) { }
                inline  QAdd(const QAdd &it)  noexcept : data(it.data), rank(it.rank) { }
                inline ~QAdd() noexcept {}

                inline friend std::ostream & operator<<(std::ostream &os, const QAdd &self) {
                    return os << '|' << self.data << '|';
                }

                inline ConstType & operator*() const noexcept { return data; }

                inline friend QAdd operator+(const QAdd &lhs, const QAdd &rhs) noexcept {
                    return QAdd(lhs.data+rhs.data);
                }

                class Comparator
                {
                public:
                    inline  Comparator() noexcept {}
                    inline ~Comparator() noexcept {}
                    inline int operator()(const QAdd &lhs, const QAdd &rhs) noexcept {
                        return (lhs.rank < rhs.rank) ? -1 : ( (rhs.rank<lhs.rank) ? 1 : 0);
                    }
                };

            private:
                ConstType data;
                ConstType rank;
                Y_Disable_Assign(QAdd);
            };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            //__________________________________________________________________
            //
            //
            //
            //! Prototype for SCALAR Queued summators
            //
            //
            //__________________________________________________________________
            template <
            typename T,
            typename PQ // Priority queue for QAdd<T>
            >
            class QueuedCode : public Summator<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Declare(T,Type); //!< alias
                typedef QAdd<T> Item;   //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline QueuedCode() : pq()                                               { Y_Cameo_Sum_Queued_Check(); } //!< setup empty
                inline QueuedCode(const size_t minCapacity) : pq(minCapacity)            { Y_Cameo_Sum_Queued_Check(); } //!< setup \param minCapacity for compatibility
                inline QueuedCode(const QueuedCode &other) : Summator<T>(), pq(other.pq) { Y_Cameo_Sum_Queued_Check(); } //!< duplicate \param other another FP_QAdd
                inline virtual ~QueuedCode() noexcept                                    {} //!< cleanup

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const QueuedCode &self)
                {
                    return os << self.pq;
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual void ldz() noexcept { pq.free(); }
                inline void         add(ConstType &data) {
                    const Item item(data); pq.push(item);
                }
                inline void         sub(ConstType &data) {
                    const Item item(-data); pq.push(item);
                }

                inline virtual Type operator()(void)
                {
                    switch(pq.size())
                    {
                        case 0: return 0;
                        case 1: return *pq.pull();
                        default:
                            break;
                    }
                    while(pq.size()>1)
                    {
                        const Item lhs = pq.pull(); assert(pq.size()>0);
                        const Item rhs = pq.pull();
                        pq << lhs+rhs;
                    }
                    assert(1==pq.size());
                    return *pq.pull();
                }

            private:
                Y_Disable_Assign(QueuedCode); //!< discarded
                PQ pq;                        //!< inner queue
            };

        }
    }

}

#endif // !Y_Cameo_Sum_Queued_Common


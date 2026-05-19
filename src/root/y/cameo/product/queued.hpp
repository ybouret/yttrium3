
//! \file

#ifndef Y_Cameo_Product_Queued
#define Y_Cameo_Product_Queued 1


#include "y/cameo/multiplier.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/core/list.hpp"
#include "y/core/pool.hpp"
#include "y/type/pulverize.hpp"
#include "y/object.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Product
        {
            namespace Pith
            {
                typedef TL3(float,double,long double)                                                 StandardFloats;    //!< \return alias
                typedef TL3(XReal<float>,XReal<double>,XReal<long double>)                            ExtendedFloats;    //!< \return alias
                typedef TL3(Complex<float>,Complex<double>,Complex<long double>)                      StandardComplexes; //!< \return alias
                typedef TL3(Complex<XReal<float>>,Complex<XReal<double>>,Complex<XReal<long double>>) ExtendedComplexes; //!< \return alias

            }

            //! compute parameters for given type
            template <typename T>
            struct ByQueuedAPI
            {
                static const bool StandardF    = ( TL::IndexOf<Pith::StandardFloats,T>::Value    >= 0 ); //!< alias
                static const bool ExtendedF    = ( TL::IndexOf<Pith::ExtendedFloats,T>::Value    >= 0 ); //!< alias
                static const bool StandardC    = ( TL::IndexOf<Pith::StandardComplexes,T>::Value >= 0 ); //!< alias
                static const bool ExtendedC    = ( TL::IndexOf<Pith::ExtendedComplexes,T>::Value >= 0 ); //!< alias
                static const bool IsProper     = StandardF || ExtendedF || StandardC || ExtendedC;       //!< alias
            };

            //! helper for static check
#define Y_Cameo_Product_Queued_Check() Y_STATIC_CHECK(ByQueuedAPI<MutableType>::IsProper,BadType)


            namespace Pith
            {
                //! rank for standard floats
                template <typename T> struct Rank
                {
                    //! \param f floating point \return exponent
                    static inline int Of(const T &f) noexcept
                    {
                        int rank = 0;
                        (void) std::frexp(f,&rank);
                        return rank;
                    }
                };

                //! rank for extended floats
                template <typename T> struct Rank< XReal<T> >
                {
                    //! \param x extended float \return exponent
                    static inline int Of(const XReal<T> &x) noexcept
                    {
                        return x.exponent;
                    }
                };

                //! rank for any complex
                template <typename T> struct Rank< Complex<T> >
                {
                    //! \param z complex \return approx exponent
                    static inline int Of(const Complex<T> &z) noexcept
                    {
                        const T az = MKL::Fabs<T>(z.re) + MKL::Fabs<T>(z.im);
                        return Rank<T>::Of(az);
                    }
                };

                //! \param value supported value \return rank for queue
                template <typename T> static inline
                int GetRank(const T &value) noexcept
                {
                    return Rank<T>::Of(value);
                }
            }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename T>
            class QMul
            {
            public:
                Y_Args_Expose(T,Type);

                inline QMul(ConstType &value) noexcept :
                data(value),
                rank( Pith::GetRank(data) ),
                next(0),
                prev(0)
                {
                }

                inline QMul(const QMul &q) noexcept :
                data(q.data),
                rank(q.rank),
                next(0),
                prev(0)
                {
                }

                inline ~QMul() noexcept {}

                inline const QMul & operator*() const noexcept { return *this; }

                inline friend std::ostream & operator<<(std::ostream &os, const QMul &self)
                {
                    return os << self.data << "#" << self.rank;
                }

                ConstType data;
                const int rank;
                QMul *    next;
                QMul *    prev;
            private:
                Y_Disable_Assign(QMul);
            };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            //__________________________________________________________________
            //
            //
            //
            //! Queued multiplication
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Queued : public Multiplier<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type); //!< alias
                typedef QMul<T> Item;  //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                inline explicit Queued() noexcept : list(), pool() { Y_Cameo_Product_Queued_Check(); }

                //! setup \param minCapacity initial pool size
                inline explicit Queued(const size_t minCapacity) :
                list(), pool()
                {
                    Y_Cameo_Product_Queued_Check();
                    try {
                        while(pool.size<minCapacity)
                            pool.store( Object::AcquireZombie<Item>() );
                    } catch(...) { quit(); throw; }
                }

                //! duplicate \param q another queued
                inline Queued(const Queued &q) : Multiplier<T>(), list(), pool()
                {
                    Y_Cameo_Product_Queued_Check();
                    try
                    {
                        for(const Item *it=q.list.head;it;it=it->next)
                            list.pushTail( new ( Object::AcquireZombie<Item>() ) Item(*it) );
                    } catch(...) { quit(); throw; }
                }

                //! cleanup
                inline virtual ~Queued() noexcept { quit(); }

                //! display content
                inline friend std::ostream & operator<<(std::ostream &os, const Queued &self)
                {
                    return os << self.list;
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual const char * callSign() const noexcept
                {
                    return "Cameo::Product::Queued";
                }


                inline virtual void ld1() noexcept { free(); }

                inline virtual void mul(ConstType &args)
                {
                    update(list.pushTail( new (pool.size?pool.query() : Object::AcquireZombie<Item>()) Item(args) ));
                }

                inline virtual Type operator()(void)
                {
                    if(list.size<=0) return 1;
                    while(list.size>1)
                    {
                        ConstType lhs = list.head->data;
                        ConstType rhs = list.tail->data; pool.store( Pulverized( list.popHead() ));
                        ConstType prd = lhs * rhs;
                        update( list.pushTail( new ( Pulverized( list.popTail()) ) Item(prd) ) );
                        std::cerr << *this << std::endl;
                    }
                    ConstType res = list.head->data;
                    pool.store( Pulverized(list.popHead()) );
                    assert(0==list.size);
                    return res;
                }



            private:
                Y_Disable_Assign(Queued); //!< discarded
                Core::ListOf<Item> list;  //!< list of living items
                Core::PoolOf<Item> pool;  //!< pool of zombie items

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                inline void update(Item * const item) noexcept
                {
                    assert(item); assert(item == list.tail);
                    while(item->prev && item->prev->rank>item->rank)
                        list.towardsHead(item);
                }

                inline void free() noexcept {
                    while(list.size) pool.store( Pulverized(list.popTail() ) );
                }

                inline void quit() noexcept {
                    while(list.size) Object::ReleaseZombie( Pulverized(list.popTail() ) );
                    while(pool.size) Object::ReleaseZombie( pool.query() );
                }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            };


        }

    }

}

#endif // !Y_Cameo_Product_Queued


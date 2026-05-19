
//! \file

#ifndef Y_Cameo_Vectorial_Summator_Included
#define Y_Cameo_Vectorial_Summator_Included 1


#include "y/cameo/sum/scalar.hpp"
#include "y/hide.hpp"
#include "y/calculus/alignment.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        namespace Sum
        {
            //__________________________________________________________________
            //
            //
            //
            //! Vectorial summator from matching Scalar summators
            //
            //
            //__________________________________________________________________
            template <typename T, typename VECT>
            class Vectorial: public Summator<VECT>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const size_t  Dimension = sizeof(VECT)/sizeof(T);                //!< alias
                typedef Scalar<T>    XAddition;                                         //!< alias
                static const size_t  Requested = Dimension*sizeof(XAddition);           //!< inner bytes
                static const size_t  WordCount = Alignment::WordsGEQ<Requested>::Count; //!< inner words
                Y_Args_Declare(VECT,Type);                                              //!< aliases
                Y_Args_Expose(T,Scal);                                                  //!< aliases

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                inline Vectorial() : xadd(0), wksp(), xnum(0) { init(); }

                //! setup \param minCapacity compatibility
                inline Vectorial(const size_t minCapacity) :
                xadd(0), wksp(), xnum(0) {
                    init(minCapacity);
                }

                //! duplicate \param other another Vectorial
                inline Vectorial(const Vectorial &other) :
                xadd(0), wksp(), xnum(0) {
                    init(other);
                }

                //! cleanup
                inline virtual ~Vectorial() noexcept { quit(); }

                //! display status
                inline friend std::ostream & operator<<(std::ostream &os, const Vectorial &self)
                {
                    os << '{' << std::endl;
                    for(size_t i=0;i<Dimension;++i)
                        os << '\t' << self.xadd[i] << std::endl;
                    return os << '}';
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                inline virtual void ldz() noexcept {
                    for(size_t i=0;i<Dimension;++i) xadd[i].ldz();
                }

                inline virtual void add(ConstType &v)
                {
                    ConstScal * const scal = Hide::Cast<ConstScal>(&v);
                    try {
                        for(size_t i=0;i<Dimension;++i) xadd[i].add(scal[i]);
                    }
                    catch(...) { ldz(); throw; }
                }

                inline virtual Type operator()(void)
                {
                    MutableType v;
                    try
                    {
                        MutableScal * const scal = Hide::Cast<MutableScal>(&v);
                        for(size_t i=0;i<Dimension;++i) scal[i] = xadd[i]();
                    }
                    catch(...) { ldz(); throw; }
                    ldz();
                    return v;
                }

                virtual const char * callSign() const noexcept { return "Cameo::Sum::Vectorial"; }

            private:
                Y_Disable_Assign(Vectorial);         //!< discarded
                XAddition * const xadd;              //!< [Dimension]
                void *            wksp[ WordCount ]; //!< inner memory
                size_t            xnum;              //!< built xadd

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                inline void init() {
                    assert(0==xadd);
                    Coerce(xadd) = static_cast<XAddition*>( Y_BZero(wksp) );
                    try {
                        while(xnum<Dimension) {
                            new (xadd+xnum) XAddition();
                            ++xnum;
                        }
                    }
                    catch(...) { quit(); throw; }
                }

                inline void init(const size_t minCapacity)
                {
                    assert(0==xadd);
                    Coerce(xadd) = static_cast<XAddition*>( Y_BZero(wksp) );
                    try {
                        while(xnum<Dimension) {
                            new (xadd+xnum) XAddition(minCapacity);
                            ++xnum;
                        }
                    }
                    catch(...) { quit(); throw; }
                }

                inline void init(const Vectorial &other)
                {
                    assert(0==xadd);
                    Coerce(xadd) = static_cast<XAddition*>( Y_BZero(wksp) );
                    try {
                        while(xnum<Dimension) {
                            new (xadd+xnum) XAddition(other.xadd[xnum]);
                            ++xnum;
                        }
                    }
                    catch(...) { quit(); throw; }
                }


                inline void quit() noexcept
                {
                    assert(xadd);
                    while(xnum>0) Destruct( &xadd[--xnum] );
                    Coerce(xadd) = 0;
                    Y_BZero(wksp);
                }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            };
        }

    }

}

#endif // !Y_Cameo_Vectorial_Summator_Included

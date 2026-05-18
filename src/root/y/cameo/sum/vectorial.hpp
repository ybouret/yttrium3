
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
            template <typename T, typename VECT>
            class Vectorial: public Summator<VECT>
            {
            public:
                static const size_t        Dimension = sizeof(VECT)/sizeof(T);
                typedef Scalar<T>          XAddition;
                static const size_t        Requested = Dimension*sizeof(XAddition);
                Y_Args_Declare(VECT,Type);
                Y_Args_Expose(T,Scal);

                inline Vectorial() :
                xadd(0), wksp(), xnum(0)
                {
                    init();
                }

                inline virtual ~Vectorial() noexcept { quit(); }

                inline friend std::ostream & operator<<(std::ostream &os, const Vectorial &self)
                {
                    os << '{' << std::endl;
                    for(size_t i=0;i<Dimension;++i)
                        os << '\t' << self.xadd[i] << std::endl;
                    return os << '}';
                }

                inline virtual void ldz() noexcept {
                    for(size_t i=0;i<Dimension;++i) xadd[i].ldz();
                }

                inline virtual void add(ParamType v)
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
                Y_Disable_Assign(Vectorial);
                XAddition * const xadd;
                void *            wksp[ Alignment::WordsGEQ<Requested>::Count ];
                size_t            xnum;

                inline void init()
                {
                    assert(0==xadd);
                    Coerce(xadd) = static_cast<XAddition*>( Y_BZero(wksp) );
                    try
                    {
                        while(xnum<Dimension)
                        {
                            new (xadd+xnum) XAddition();
                            ++xnum;
                        }
                    }
                    catch(...)
                    {
                        quit(); throw;
                    }
                }
                
                inline void quit() noexcept
                {
                    assert(xadd);
                    while(xnum>0) Destruct( &xadd[--xnum] );
                    Coerce(xadd) = 0;
                    Y_BZero(wksp);
                }
            };
        }

    }

}

#endif // !Y_Cameo_Vectorial_Summator_Included

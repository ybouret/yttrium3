
//! \file

#ifndef Y_Cameo_Sum_Raised
#define Y_Cameo_Sum_Raised 1


#include "y/cameo/sum/api/raised.hpp"
#include "y/cameo/summator.hpp"

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
            //! Raised, Scalar summator: integral to arbitrary precision
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Raised : public Summator<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type);                                        //!< aliases
                typedef typename ByRaisedAPI<MutableType>::Type Accumulator; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Raised()              : acc(0)         { Y_Cameo_Sum_Raised_Check(); } //!< setup
                inline explicit Raised(const size_t ) : acc(0)         { Y_Cameo_Sum_Raised_Check(); } //!< setup, compativility
                inline Raised(const Raised &other)    : acc(other.acc) { Y_Cameo_Sum_Raised_Check(); } //!< duplicate \param other another Raised
                inline virtual ~Raised() noexcept                      { acc.ldz(); }                  //!< cleanup

                //! display status
                inline friend std::ostream & operator<<(std::ostream &os, const Raised &self)
                {
                    return os << self.acc;
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual void ldz()       noexcept { acc.ldz(); }
                inline virtual void add(ConstType &data) { acc += data; }
                inline virtual void sub(ConstType &data) { acc -= data; }
                inline virtual Type operator()(void)
                {
                    ConstType res = acc.template cast<MutableType>(0,0);
                    acc.ldz();
                    return res;
                }

                inline virtual const char * callSign() const noexcept
                {
                    return "Cameo::Sum::Raised";
                }


            private:
                Y_Disable_Assign(Raised); //!< discarded
                Accumulator acc;          //!< inner accumulator
            };

        }

    }

}

#endif // !Y_Cameo_Sum_Raised

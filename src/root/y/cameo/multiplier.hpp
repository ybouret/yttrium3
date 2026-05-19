
//! \file

#ifndef Y_Cameo_Multiplier_Included
#define Y_Cameo_Multiplier_Included 1

#include "y/container.hpp"
#include "y/type/args.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        //______________________________________________________________________
        //
        //
        //
        //! Multiplier interface
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Multiplier : public Identifiable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit Multiplier() noexcept {} //!< setup
            inline virtual ~Multiplier() noexcept {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void ld1() noexcept     = 0; //!< reset
            virtual void mul(ConstType &)   = 0; //!< mul by data
            virtual Type operator()(void)   = 0; //!< \return result (MUST be 1 afterwards)

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________

            //! helper \param data to add \return *this
            inline Multiplier & operator<<(ParamType data) {
                mul(data); return *this;
            }

            //! helper \param data to add \return *this
            inline Multiplier & operator *=(ParamType data) {
                mul(data); return *this;
            }

            //! helper \param data to set \return *this
            inline Multiplier & operator=(ParamType data) {
                ld1(); mul(data); return *this;
            }

        private:
            Y_Disable_Copy_And_Assign(Multiplier); //!< discarded
        };

    }

}

#endif // !Y_Cameo_Multiplier_Included


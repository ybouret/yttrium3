//! \file

#ifndef Y_Cameo_Summator_Included
#define Y_Cameo_Summator_Included 1

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
        //! Summator interface
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Summator : public Identifiable
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
            inline explicit Summator() noexcept {} //!< setup
            inline virtual ~Summator() noexcept {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void ldz() noexcept   = 0; //!< reset
            virtual void add(ConstType &) = 0; //!< add data
            virtual Type operator()(void) = 0; //!< \return result (MUST be zero afterwards)

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________

            //! helper \param data to add \return *this
            inline Summator & operator<<(ParamType data) {
                add(data); return *this;
            }

            //! helper \param data to add \return *this
            inline Summator & operator +=(ParamType data) {
                add(data); return *this;
            }

            //! helper \param data to set \return *this
            inline Summator & operator=(ParamType data) {
                ldz(); add(data); return *this;
            }

        private:
            Y_Disable_Copy_And_Assign(Summator); //!< discarded
        };

    }

}

#endif // !Y_Cameo_Summator_Included


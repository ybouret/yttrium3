
//! \file

#ifndef Y_Jive_Matching_Included
#define Y_Jive_Matching_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Matching engine for Module
        //
        //
        //______________________________________________________________________
        class Matching : public Token, public Motif
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! matching Request
            enum Request
            {
                Exactly, //!< full module must match pattern
                Somehow  //!< partial module must match pattern
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Matching(Pattern * const) noexcept; //!< setup
            virtual ~Matching()                noexcept; //!< setup
            Matching(const char * const);
            Matching(const String &);
            Matching(const Matching &);
            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool operator()(const Request , Module * const); //!< \return dispatched call
            bool exactly(Module * const); //!< \return true iff full module matches pattern
            bool somehow(Module * const); //!< \return true iff pattern is found in module

            template <typename NAME, typename DATA> inline
            bool found(const Request how, const NAME & moduleName, const DATA & moduleData )
            {
                return (*this)(how, Module::OpenData(moduleName,moduleData) );
            }


        private:
            Y_Disable_Assign(Matching); //!< discarded
        };

    }

}

#endif // !Y_Jive_Matching_Included


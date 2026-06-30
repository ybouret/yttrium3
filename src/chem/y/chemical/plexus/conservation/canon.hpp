//! \file

#ifndef Y_Chemical_Conservation_Canon_Included
#define Y_Chemical_Conservation_Canon_Included 1

#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/type/sp-roll.hpp"
#include "y/chemical/type/assembly.hpp"
#include "y/chemical/type/matrix.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

            typedef Handy::BasicLightList<const Law> LList; //!< alias
            typedef LList::NodeType                  LNode; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! list of interwoven laws and their species
            //
            //
            //__________________________________________________________________
            class Canon : public Object
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxListOf<Canon> List; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Canon(const Law &); //!< setup with first law
                virtual ~Canon() noexcept;   //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                bool accepts(const Law &) const noexcept; //!< \return true iff shared species
                void compile();                           //!< inscribe and AuxLabel species, update format

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                SpDB     species; //!< database of involved species
                LList    laws;    //!< list of laws
                Canon *  next;    //!< for list
                Canon *  prev;    //!< for list
                UMatrix  Gamma;   //!< compact conservation matrix
                size_t   rg;      //!< rank(Gamma)
                Assembly lfmt;    //!< to format

            private:
                Y_Disable_Copy_And_Assign(Canon); //!< discarded
            };
        }

    }

}

#endif // !Y_Chemical_Conservation_Canon_Included

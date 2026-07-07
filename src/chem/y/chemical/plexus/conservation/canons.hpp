
#ifndef Y_Chemical_Conservation_Canons_Included
#define Y_Chemical_Conservation_Canons_Included 1

#include "y/chemical/plexus/conservation/canon.hpp"
#include "y/xml/log.hpp"
#include "y/chemical/type/assembly.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            //__________________________________________________________________
            //
            //
            //
            //! independent lists of dependent laws
            //
            //
            //__________________________________________________________________
            class Canons : public Proxy<const Canon::List>
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup for list of laws
                explicit Canons(XML::Log                &xml,
                                const Core::ListOf<Law> &laws,
                                const IMatrix           &topNuT,
                                const Assembly          &lfmt);

                //! cleanup
                virtual ~Canons() noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            private:
                Y_Disable_Copy_And_Assign(Canons); //!< discarded
                Y_Proxy_Decl();                    //!< helper
                Canon::List list;                  //!< inner list

                void makeContent(XML::Log                &,
                                 const Core::ListOf<Law> &,
                                 const Assembly          &);
                void postProcess(XML::Log &, const IMatrix &);
            };
        }

    }

}

#endif // !Y_Chemical_Conservation_Canons_Included


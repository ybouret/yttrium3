

#ifndef Y_Chemical_MixedEquilibrium_Included
#define Y_Chemical_MixedEquilibrium_Included 1

#include "y/chemical/reactive/elist.hpp"
#include "y/chemical/slist.hpp"
#include "y/handy/basic/heavy/list.hpp"
#include "y/chemical/type/defs.hpp"
#include "y/container/cxx/array.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        
        typedef Handy::BasicHeavyList<int> IList; //!< alias
        typedef IList::NodeType            INode; //!< alias


        //______________________________________________________________________
        //
        //
        //
        //! Mixed equilibrium
        //
        //
        //______________________________________________________________________
        class MixedEquilibrium : public Equilibrium
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! \return mixed name
            static String MakeName(const EList &, const IList &);

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! \return created and populated new mixed equilibrium
            static MixedEquilibrium * Create(const size_t,
                                             const EList     &,
                                             const IList     &,
                                             const SList     &,
                                             const IList     &,
                                             const XReadable &);


            virtual ~MixedEquilibrium() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const CxxArray<size_t>  itop;  //!< top indices
            const CxxArray<int>     coef;  //!< coefficient
            XMul                    numer; //!< helper for numerator
            XMul                    denom; //!< helper for denominator
            const XReadable       & topK;  //!< top level K stored

        private:
            Y_Disable_Copy_And_Assign(MixedEquilibrium); //!< discarded

            //! setup without actors
            MixedEquilibrium(const String &,
                             const size_t,
                             const EList     & ,
                             const IList     & ,
                             const XReadable &);

            virtual xreal_t getK(const xreal_t);
        };
    }

}

#endif // !Y_Chemical_MixedEquilibrium_Included




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
        
        typedef Handy::BasicHeavyList<int> IList;
        typedef IList::NodeType            INode;


        class MixedEquilibrium : public Equilibrium
        {
        public:
            typedef Handy::BasicHeavyList<unsigned> UList;
            typedef UList::NodeType                 UNode;

            static String MakeName(const EList &, const IList &);

            static MixedEquilibrium * Create(const size_t,
                                             const EList &,
                                             const IList &,
                                             const SList &,
                                             const IList &,
                                             const XReadable &);


            virtual ~MixedEquilibrium() noexcept;

            const CxxArray<size_t>  itop;
            const IList             coef;
            XMul                    numer;
            XMul                    denom;
            const XReadable       & topK;

        private:
            Y_Disable_Copy_And_Assign(MixedEquilibrium);
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



#include "y/jive/pattern/joker/optional.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Optional:: ~Optional() noexcept
        {
        }

        Optional:: Optional(const Motif &m) noexcept :
        Joker(UUID,m)
        {
        }

        Optional:: Optional(const Optional &opt) :
        Joker(opt)
        {
        }

        Pattern * Optional:: clone() const
        {
            return new Optional(*this);
        }

        bool Optional:: univocal() const noexcept
        {
            return false;
        }

        size_t Optional:: serialize(OutputStream &fp) const
        {
            const size_t res = emitUUID(fp);
            return res+motif->serialize(fp);
        }

        bool Optional:: sound() const noexcept
        {
            return false;
        }

        bool Optional:: takes(Token &token, Source &source) const
        {
            assert(0==token.size);
            
            if( motif->takes(token,source) )
            {
                return true;
            }
            else
            {
                return true;
            }

        }

        Optional * Optional::Make(Pattern * const p)
        {
            const Motif m = p;
            return new Optional(p);
        }


        OutputStream & Optional:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp,"?") << ",shape=diamond";
            Endl(fp<<']');
            return emitLink(fp);
        }

        Pattern * Optional:: optimized()
        {
            optimizeMotif();
            return this;
        }

        Pattern * Optional:: insensitive()
        {
            return this;
        }
    }

}

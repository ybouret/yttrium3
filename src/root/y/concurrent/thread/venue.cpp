
#include "y/concurrent/thread/venue.hpp"
#include "y/system/hardware.hpp"
#include "y/string/env.hpp"
#include "y/ascii/convert.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"

#include <cctype>
#include <cstring>

namespace Yttrium
{
    namespace Concurrent
    {


        VenueList:: VenueList() noexcept : CountedObject(), VList() {}

        VenueList:: ~VenueList() noexcept
        {
        }



        const char * const Venue:: CallSign = "Y_NUM_THREADS";


        Venue:: Venue(const size_t ncpu) : SharedVList( new VenueList() )
        {
            if(ncpu<=0)
            {
                // trigger environment look up
                const String name = CallSign;
                String       info;
                if(Environment::Get(info,name))
                {
                    // parse info
                    parse(info);
                }
                else
                {
                    // no info => fallback
                    linear( Hardware::NumProcs() );
                }
            }
            else
                // specific cpu count, linear
                linear(ncpu);
        }

        Venue:: Venue(const Venue &v) noexcept : SharedVList(v)
        {
        }

        Venue:: ~Venue() noexcept
        {
        }
        

        void Venue:: linear(const size_t n)
        {
            if(n<=0) throw Specific::Exception(CallSign,"unexpect zero count");
            for(size_t i=0;i<n;++i)
                **this << i;
        }

        

        void Venue:: parse(String &info)
        {
            Algorithm::Crop(info,isspace);

            // check avdanced parsing
            {
                const char * const org = info.c_str();
                std::cerr << "parsing '" << org << "'" << std::endl;
                if(strchr(org,COLON))
                {
                    parseCode(info);
                    return;
                }

                if(strchr(org,COMA))
                {
                    parseList(info);
                    return;
                }
            }

            // assuming empty or single
            if(info.size()<=0)
            {
                linear( Hardware::NumProcs() );
            }
            else
            {
                linear( ASCII::Convert::To<size_t>(info,CallSign,"#CPU") );
            }

        }

        namespace
        {
            static inline
            size_t parseField(String &field, const char * const name)
            {
                assert(0!=name);
                Algorithm::Crop(field,isspace);
                return ASCII::Convert::To<size_t>(field,Venue::CallSign,name);
            }
        }


        void Venue:: parseCode(const String &info)
        {

            size_t       ncpu   = 0;
            size_t       offset = 0;
            size_t       step   = 1;
            {
                Vector<String> indx;
                Tokenizer::AppendTo(indx,info,COLON); assert(indx.size()>0);
                const size_t f = indx.size();
                switch(f)
                {
                    case 3: step   = parseField(indx[3],"step");   // FALLTHRU
                    case 2: offset = parseField(indx[2],"offset"); // FALLTHRU
                    case 1: ncpu   = parseField(indx[1],"#cpu");
                        break;

                    default:
                        throw Specific::Exception(CallSign,"invalid %s fields", Decimal(f).c_str());
                }
            }

            // std::cerr << "ncpu   = " << ncpu   << std::endl;
            // std::cerr << "offset = " << offset << std::endl;
            // std::cerr << "step   = " << step   << std::endl;

            if(ncpu<=0) throw Specific::Exception(CallSign,"zero core");
            if(step<=0) throw Specific::Exception(CallSign,"null step");

            const size_t nmax = Hardware::NumProcs();
            size_t       icpu = offset;
            for(size_t i=ncpu;i>0;--i,icpu+=step)
            {
                (**this) << (icpu%nmax);
            }



        }

        void Venue:: parseList(const String &info)
        {
            Vector<String> indx;
            Tokenizer::AppendTo(indx,info,COMA); assert(indx.size()>0);
            const size_t n = indx.size();
            for(size_t i=1;i<=n;++i)
            {
                const String  label = Formatted::Get("cpu#%s", Decimal(n).c_str());
                String      & id    = Algorithm::Crop(indx[i],isspace);
                (**this) << ASCII::Convert::To<size_t>(id,CallSign,label.c_str());
            }
        }


    }

}

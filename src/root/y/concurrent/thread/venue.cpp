
#include "y/concurrent/thread/venue.hpp"
#include "y/system/hardware.hpp"
#include "y/string/env.hpp"
#include "y/ascii/convert.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/algorithm/crop.hpp"
#include <cctype>

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

        void Venue:: parseCode(const String &info)
        {

            std::cerr << "no parseCode" << std::endl;
            exit(1);
        }

        void Venue:: parseList(const String &info)
        {
            std::cerr << "no parseList" << std::endl;
            exit(1);
        }


    }

}

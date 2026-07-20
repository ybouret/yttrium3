
#include "y/ink/histogram/build.hpp"

namespace Yttrium
{
    namespace Ink
    {

        BuildHistogram:: Ops::  Ops() noexcept {}
        BuildHistogram:: Ops:: ~Ops() noexcept {}

        void BuildHistogram:: Merge(Histogram &H, Broker &broker)
        {
            for(size_t i=broker.size();i>0;--i)
            {
                assert(broker[i].bytes >= Ops::Bytes);
                H.merge( static_cast<freq_t*>( broker[i].entry) );
            }
        }

    }

}


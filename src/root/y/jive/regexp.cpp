
#include "y/jive/regexp.hpp"
#include "y/jive/regexp/compiler.hpp"
#include "y/pointer/auto.hpp"
#include "y/string/length.hpp"

#include "y/jive/pattern/basic/byte.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Pattern * RegExp:: Compile(const String &data, const Dictionary * const dict)
        {
            return Compile_( data.c_str(), data.size(), dict);
        }

        Pattern * RegExp:: Compile(const char * const data, const Dictionary * const dict)
        {

            return Compile_(data,StringLength(data),dict);
        }

        Pattern * RegExp:: Compile(const Identifier &data, const Dictionary * const dict)
        {
            return Compile_(data->c_str(),data->size(),dict);
        }

        Pattern * RegExp:: Compile(const char c, const Dictionary * const)
        {
            return new Byte( (uint8_t) c );
        }


        Pattern * RegExp:: Compile_(const char * const buffer,
                                    const size_t       length,
                                    const Dictionary * const dict)
        {
            assert( !(0==buffer&&length>0));
            RXCompiler       rxc(buffer,length,dict);
            AutoPtr<Pattern> rx = rxc();
            return rx.yield();
        }
    }

}

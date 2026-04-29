//! \file

#ifndef Y_Jive_Module_Included
#define Y_Jive_Module_Included 1

#include "y/jive/char.hpp"
#include "y/stream/memory/input.hpp"

namespace Yttrium
{
    namespace Jive
    {

        typedef ArcPtr<InputStream> Input;

        class Module : public Object, public Spot
        {
        public:
            explicit Module( const Input & ) noexcept;
            virtual ~Module() noexcept;


            Char * get();
            void   newLine() noexcept;


            static Module * OpenFile(const String &fileName);
            static Module * OpenFile(const char * const fileName);
            static Module * OpenStdIn();

            template <typename NAME> inline
            static Module * OpenData(const NAME &       name,
                                     const void * const buffer,
                                     const size_t       buflen)
            {
                const Input in( new InputMemoryStream(name,buffer,buflen) );
                return new Module(in);
            }

            template <typename NAME> inline
            static Module * OpenData(const NAME &                   name,
                                     const Memory::ReadOnlyBuffer & buff)
            {
                const Input in( new InputMemoryStream(name,buff) );
                return new Module(in);
            }

            template <typename NAME> inline
            static Module * OpenData(const NAME &       name,
                                     const char * const text)
            {
                const Input in( new InputMemoryStream(name,text) );
                return new Module(in);
            }



        private:
            Y_Disable_Copy_And_Assign(Module);
            Input input;
        };



    }

}

#endif // !Y_Jive_Module_Included


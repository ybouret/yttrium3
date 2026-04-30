//! \file

#ifndef Y_Jive_Module_Included
#define Y_Jive_Module_Included 1

#include "y/jive/char.hpp"
#include "y/stream/memory/input.hpp"

namespace Yttrium
{
    namespace Jive
    {

        typedef ArcPtr<InputStream> Input; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Transform InputStream to Char provider
        //
        //
        //______________________________________________________________________
        class Module : public Object, public Spot
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Module( const Input & ) noexcept; //!< setup
            virtual ~Module()                noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Char * get();              //!< \return new char from input
            void   newLine() noexcept; //!< modify location


            static Module * OpenFile(const String &);      //!< \return new module from file name
            static Module * OpenFile(const char * const);  //!< \return new module from file name
            static Module * OpenStdIn();                   //!< \return new module from stdin

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
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
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)


        private:
            Y_Disable_Copy_And_Assign(Module); //!< discarded
            Input input; //!< inner input
        };



    }

}

#endif // !Y_Jive_Module_Included


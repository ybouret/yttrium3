//! \file

#ifndef Y_Type_DetectMember_Included
#define Y_Type_DetectMember_Included 1


namespace Yttrium
{

#define Y_DetectMember(PREFIX,MEMBER)                                        \
/**/    template <typename T> struct PREFIX ## MEMBER {                      \
/**/        typedef char Yes[1]; typedef char No[2];                         \
/**/        template <typename C> static Yes & test( decltype(C::MEMBER) *); \
/**/        template <typename>   static No  & test(...);                    \
/**/        static const bool Value = (sizeof(test<T>(0)) == sizeof(Yes));   \
/**/    }



}

#endif // !Y_Type_DetectMember_Included

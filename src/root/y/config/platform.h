//! \file

#ifndef Y_Platform_Included
#define Y_Platform_Included

#if defined(Y_Platform)
#error "Y_Platform shouldn't be defined!"
#endif

#if defined(__APPLE__)
#define Y_Platform "Darwin"
#define Y_Darwin   1
#define Y_BSD      1
#endif

#if defined(__linux__)
#define Y_Platform "Linux"
#define Y_Linux    1
#define Y_BSD      1
#endif

#if defined(__FreeBSD__)
#define Y_Platform "FreeBSD"
#define Y_FreeBSD  1
#define Y_BSD      1
#endif


#if defined(__NetBSD__)
#define Y_BSD       1
#define Y_Platform "NetBSD"
#define Y_NetBSD    1
#endif

#if defined(__sun__)
#define Y_BSD       1
#define Y_Platform "SunOS"
#define Y_SunOS
#endif


#if defined(_WIN32) || defined(_WIN64)
#define Y_WIN       1
#define Y_Platform "Windows"
#endif


#if !defined(Y_Platform)
#error "Y_Platform SHOULD be defined!"
#endif

#if !defined(Y_BSD) && !defined(Y_WIN)
#error "missing BSD/WIN API selection"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

    extern const char * const Yttrium_Platform; //!< set as Y_Platform

#if defined(__cplusplus)
}
#endif

#if defined(_MSC_VER)

#if (_MSC_VER<=1916)

#pragma warning ( disable : 4625 ) 
#pragma warning ( disable : 4626 ) 
#pragma warning ( disable : 5026 ) 
#pragma warning ( disable : 5027 ) 
#pragma warning ( disable : 4774 ) 
#pragma warning ( disable : 4571 )

#endif


#endif


#endif // !Y_Platform_Included



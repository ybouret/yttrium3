
//! \file

#ifndef Y_Libc_Rand_Included
#define Y_Libc_Rand_Included 1


#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! fast portable uniform random generator, float version
    /**
     \param seed internal state, update
     \return value in ]0:1[
     */
    //__________________________________________________________________________
    float       Yttrium_Randf(long * const seed);

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
    double      Yttrium_Rand(long * const seed);
    long double Yttrium_Randl(long * const seed);
#endif
    
#if defined(__cplusplus)
}
#endif

#endif // !Y_Libc_Rand_Included


//! \file

#ifndef Y_Config_Setup_H_Included
#define Y_Config_Setup_H_Included

#include "y/config/platform.h"
#include "y/config/compiler.h"

#if defined(__cplusplus)
#include <cstdlib>
#else
#include <stdlib.h>
#endif

//! inline static size of an array
#define Y_Static_Size(ARR) ( sizeof(ARR) / sizeof(ARR[0]) )

#if defined(NDEBUG)
#define Y_DEBUG(EXPR)
#else
//! conditional expression output
#define Y_DEBUG(EXPR) EXPR
#endif

#endif // !Y_Config_Setup_H_Included



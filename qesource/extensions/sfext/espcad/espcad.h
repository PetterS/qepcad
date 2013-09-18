/**************************************************

This file "defines" the ESPCAD structure.

***************************************************/
#ifndef _ESPCAD_
#define _ESPCAD_

#include "qepcad.h"
#include "coarsecad.h"

#define SC_SIGN 5
#define SC_EXTS 6
#define SC_TMPM 7
#define SC_RRNV 8

#ifndef BDCOMP
#define BDCOMP(a,b)       ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
#endif

#endif /* _ESPCAD_ */

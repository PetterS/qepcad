/*======================================================================
<macro>               t <- ISATOM(a)

Test for atom.

Inputs
  a  : a Word.

Outputs
  t  :  a BETA-digit.
        t = 1 if a is an atom,
        t = 0 otherwise.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word ISATOM(a)
       Word a;
{
 return(-BETA < a && a < BETA);
}

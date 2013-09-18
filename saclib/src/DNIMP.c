/*======================================================================
<macro>               c <- DNIMP(a,b)

Digit non-implication.

Inputs
  a,b : non-negative BETA-digits.

Outputs
  c : the bit-wise non-implication of a and b.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word DNIMP(a,b)
       Word a,b;
{
       Word a1,ap,b1,bp,c,cp;
       /* hide a1,ap,b1,bp,c,cp; */

Step1: /* Compute. */
       if (a == 0)
         c = 0;
       else
         {
         QREM(a,2,&ap,&a1);
         QREM(b,2,&bp,&b1);
         cp = DNIMP(ap,bp);
         c = cp + cp;
         if (a1 == 1 && b1 == 0)
           c = c + 1;
         }

Return: /* Prepare for return. */
       return(c);
}

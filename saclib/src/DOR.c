/*======================================================================
<macro>               c <- DOR(a,b)

Digit or.

Inputs
  a,b : non-negative BETA-digits.

Outputs
  c : the bit-wise or of a and b.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word DOR(a,b)
       Word a,b;
{
       Word a1,ap,b1,bp,c,cp;
       /* hide a1,ap,b1,bp,c,cp; */

Step1: /* Compute. */
       if (a == 0)
         c = b;
       else
         if (b == 0)
           c = a;
         else
           {
           QREM(a,2,&ap,&a1);
           QREM(b,2,&bp,&b1);
           cp = DOR(ap,bp);
           c = cp + cp;
           if (a1 > 0 || b1 > 0)
             c = c + 1;
           }

Return: /* Prepare for return. */
       return(c);
}

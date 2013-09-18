/*======================================================================
                      a <- RNFLOR(r)

Rational number, floor of.  

Inputs
  r : a rational number.  

Outputs
  a : floor(r), an integer.
======================================================================*/
#include "saclib.h"

Word RNFLOR(r)
       Word r;
{
       Word a,b,r1,r2,s;
       /* hide r1,r2,s; */

Step1: /* r=0. */
       if (r == 0)
         {
         a = 0;
         goto Return;
         }

Step2: /* r /= 0. */
       FIRST2(r,&r1,&r2);
       IQR(r1,r2,&a,&b);
       s = ISIGNF(b);
       if (s < 0)
         a = ISUM(a,s);

Return: /* Prepare for return. */
       return(a);
}

/*======================================================================
                      s <- IUPBES(A,a)

Integral univariate polynomial binary rational evaluation of sign.

Inputs
  A : in Z[X].
  a : binary rational number. 

Outputs
  s : in Z, s = sign(A(a)).
======================================================================*/
#include "saclib.h"

Word IUPBES(A,a)
       Word A,a;
{
       Word b,c,d,m,s;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         s = 0;
       else
         {
         if (a == 0)
           {
           c = 0;
           m = 0;
           }
         else
           {
           FIRST2(a,&c,&d);
           m = IORD2(d);
           }
         b = IUPBEI(A,c,m);
         s = ISIGNF(b);
         }

Return: /* Prepare for return. */
       return(s);
}

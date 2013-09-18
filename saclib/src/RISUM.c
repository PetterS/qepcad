/*======================================================================
                      d <- RISUM(I,J)

Rational interval sum.

Inputs
  I, J : rational intervals.  

Outputs
  K : a rational interval. K=I+J.
======================================================================*/
#include "saclib.h"

Word RISUM(I,J)
       Word I,J;
{
       Word K;  
       Word a1,a2,b1,b2,c1,c2;

Step1: /* Get endpoints of I and J. */
       FIRST2(I,&a1,&a2);
       FIRST2(J,&b1,&b2);

Step2: /* Add corresponding endpoints. */
       c1 = RNSUM(a1,b1);
       c2 = RNSUM(a2,b2);

Step3: /* Construct list for K. */
       K = LIST2(c1,c2);

Return:
       return(K);
}

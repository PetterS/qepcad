/*======================================================================
                      a <- AFFINT(M)

Algebraic number field element from integer.  

Inputs
  M : in Z.

Outputs
  a : in Q(alpha). a = M  represented as an element of Q(alpha).
======================================================================*/
#include "saclib.h"

Word AFFINT(M)
       Word M;
{
       Word R,a;

Step1: 
       if (M == 0)
         a = 0;
       else
         {
         R = RNINT(M);
         a = LIST2(R,PMON(1,0));
         }

Return: /* Prepare for return. */
       return(a);
}

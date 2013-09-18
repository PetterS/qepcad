/*======================================================================
                        B <- IPTR1(r,A,i)

Integral polynomial translation by one, specified variable.

Inputs:
  r : A BETA-digit.  r >= 0.
  A : an element of Z[X1,...,Xr].
  i : 1 <= i <= r.

Outputs
  B : an element of Z[X1,...,Xr].  
      B(X1,...,Xi,...,Xr) = 
      A(X1,...,X{i-1},Xi + 1,X{i+1},...,Xr).
======================================================================*/
#include "saclib.h"

Word IPTR1(r,A,i)
       Word r,A,i;
{
       Word B;
       Word At,Bt;

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* i=1. */
       if (i == 1)
         {
         B = IPTR1LV(r,A);
         goto Return;
         }

Step3: /* i>1. */
       At = PCPV(r,A,1,i);
       Bt = IPTR1LV(r,At);
       B = PICPV(r,Bt,1,i);

Return:
       return(B);
}

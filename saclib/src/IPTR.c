/*======================================================================
                       B <- IPTR(r,A,i,h)

Integral polynomial translation, specified variable.

Inputs
  r : A BETA-digit.  r >= 0.
  A : an element of Z[X1,...,Xr].
  i : 1 <= i <= r.

Outputs

  B : an element of Z[X1,...,Xr].  
      B(X1,...,Xi,...,Xr) = 
      A(X1,...,X{i-1},Xi + h,X{i+1},...,Xr).
======================================================================*/
#include "saclib.h"

Word IPTR(r,A,i,h)
       Word r,A,i,h;
{
       Word B;
       Word At,Bt;

Step1: /*[A=0.]*/
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* i=1. */
       if (i == 1)
         {
         B = IPTRLV(r,A,h);
         goto Return;
         }

Step3: /* i>1. */
       At = PCPV(r,A,1,i);
       Bt = IPTRLV(r,At,h);
       B = PICPV(r,Bt,1,i);

Return:
       return(B);
}

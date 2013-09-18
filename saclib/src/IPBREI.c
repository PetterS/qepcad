/*======================================================================
                           B <- IPBREI(r,A,i,c)

Integral polynomial binary rational evaluation, integral polynomial
result.

Inputs
  r : A BETA-digit.  r >= 0.
  A : an element of Z[X1,...,Xr].
  i : 1 <= i <= r.
  c : a binary rational number. c = c0/2^k.

Outputs
  B : an element of Z[X1,...,X{i-1},X{i+1},...,Xr].  
      B(X1,...,X{i-1},X{i+1},...,Xr) = 
      2^{k * mi}A(X1,...,X{i-1},c,X{i+1},...,Xr), where mi = deg_{Xi}(A(X)).
======================================================================*/
#include "saclib.h"

Word IPBREI(r,A,i,c)

       Word r,A,i,c;
{
       Word B;
       Word At,c0,c1,k,m;

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* Initialize. */
       m = PDEGSV(r,A,i);
       if (c == 0)
         {
         c0 = 0;
         k = 0;
         }
       else
         {
         FIRST2(c,&c0,&c1);
         k = IORD2(c1);
         }

Step3: /* i=1. */
       if (i == 1)
         {
         B = IPBEILV(r,A,c0,k,m);
         goto Return;
         }

Step4: /* i>1. */
       At = PCPV(r,A,1,i);
       B = IPBEILV(r,At,c0,k,m);

Return:
       return(B);
}

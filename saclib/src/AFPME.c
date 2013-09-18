/*===========================================================================
                         B <- AFPME(r,M,A,b)

Algebraic number field polynomial multiple evaluation.

Inputs
  r : a BETA-digit, r >= 1.
  M : in Z[x], the minimal polynomial of an algebraic number alpha.  
  A : in Q(alpha)[X1,...,Xr].
  b : a list (b1,...,bk) of elements of Q(alpha), 1 <= k <= r.  

Outputs
  B : in Q(alpha)[X_{k+1},...,Xr], B = A(b1,...,bk,X_{k+1},...,Xr).
===========================================================================*/
#include "saclib.h"

Word AFPME(r,M,A,b)
       Word r,M,A,b;
{
       Word B,b1,bp,i;

Step1: /* Evaluate. */
       i = 0;
       bp = b;
       B = A;
       do {
         i++;
         ADV(bp,&b1,&bp);
         B = AFPEV(r - i + 1,M,B,1,b1); }
       while (bp != NIL);

Return: /* Prepare for return. */
       return(B);
}

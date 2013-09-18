/*======================================================================
                      B <- AFPEV(r,M,A,i,a)

Algebraic number field polynomial evaluation.  

Inputs
  r : a BETA-digit, r >= 1.
  M : in Z[x], the minimal polynomial of an algebraic number alpha.  
  A : in Q(alpha)[X1,...,Xr]. 
  i : a BETA-digit, 1 <= i <= r. 
  a : in Q(alpha).

Outputs
  B : in Q(alpha)[X1,...,X_{i-1},X_{i+1},...,Xr].
      B(X1,...,X_{i-1},X_{i+1},...,Xr) = A(X1,...,X_{i-1},a,X_{i+1},...,Xr).
======================================================================*/
#include "saclib.h"

Word AFPEV(r,M,A,i,a)
       Word r,M,A,i,a;
{
       Word A1,Ap,B,B1,e1,rp;
       /* hide A1,rp; */

Step1: /* A = 0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* i = r. */
       if (i == r)
         {
         B = AFPEMV(r,M,A,a);
         goto Return;
         }

Step3: /* i < r. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       do
         {
         ADV2(Ap,&e1,&A1,&Ap);
         B1 = AFPEV(rp,M,A1,i,a);
         if (B1 != 0)
           B = COMP2(B1,e1,B);
         }
       while (!(Ap == NIL));
       B = INV(B);
       if (B == NIL)
         B = 0;

Return: /* Prepare for return. */
       return(B);
}

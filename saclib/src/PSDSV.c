/*======================================================================
                      B <- PSDSV(r,A,i,n)

Polynomial special decomposition, specified variable.

Inputs
  A : in R[X1,...,Xr], R ring.
  r : a BETA-digit, r >=1.
  i : a BETA-digit, 1 <= i <= r.
  n : a BETA-digit such that each exponent of Xi occurring in A
      is divisible by n.  
Outputs
  B : in R[X1,...,Xr],B is A with each exponent e of Xi replaced by e/n.
======================================================================*/
#include "saclib.h"

Word PSDSV(r,A,i,n)
       Word r,A,i,n;
{
       Word Ap,B,a,b,e,f,rp;
       /* hide rp; */

Step1: /* A = 0 or n = 0. */
       if (A == 0 || n == 0)
         {
         B = A;
         goto Return;
         }

Step2: /* General case. */
       Ap = A;
       B = NIL;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (i == r)
           {
           b = a;
           f = e / n;
           }
         else
           {
           b = PDPV(rp,a,i,n);
           f = e;
           }
         B = COMP2(b,f,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}

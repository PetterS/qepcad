/*======================================================================
                      n <- PDEGSV(r,A,i)

Polynomial degree, specified variable.

Inputs
  A : in R[X1,...,Xr], R a ring.
  r : a BETA-digit, r >= 1.
  i : a BETA-digit, 1 <= i <= r.

Outputs
  n : the degree of A in the i-th variable.
======================================================================*/
#include "saclib.h"

Word PDEGSV(r,A,i)
       Word r,A,i;
{
       Word Ap,a,e,n,n1,rp;
       /* hide a,e,n,n1,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         n = 0;
         goto Return;
         }

Step2: /* i=r. */
       if (i == r)
         {
         n = PDEG(A);
         goto Return;
         }

Step3: /* General case. */
       n = 0;
       Ap = A;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         n1 = PDEGSV(rp,a,i);
         n = MAX(n,n1);
         }
       while (Ap != NIL);

Return: /* Prepare for return. */
       return(n);
}

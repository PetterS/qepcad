/*======================================================================
                      C <- MPRES(r,p,A,B)

Modular polynomial resultant.

Inputs
   r : a BETA-digit, r > 0.
   p : a BETA-digit, prime.
 A,B : in Z/(p)[X1,...,Xr], A and B are of positive degree.

Outputs
  C  : in Z/(p)[X1,...,X_{r-1}], the resultant of A and B.
======================================================================*/
#include "saclib.h"

Word MPRES(r,p,A,B)
       Word r,p,A,B;
{
       Word As,Bs,C,Cs,D,Dp,b,i,k,m,m1,n,n1,rp;

Step1: /* r=1. */
       if (r == 1) {
         C = MUPRES(p,A,B);
         goto Return; }

Step2: /* Initialize. */
       m = PDEG(A);
       m1 = PDEGSV(r,A,1);
       n = PDEG(B);
       n1 = PDEGSV(r,B,1);
       k = m * n1 + m1 * n;
       rp = r - 1;
       C = 0;
       D = LIST2(0,1);
       i = 0;

Step3: /* Recursion. */
       while (i < p) {
         As = MPEVAL(r,p,A,1,i);
         if (PDEG(As) == m) {
           Bs = MPEVAL(r,p,B,1,i);
           if (PDEG(Bs) == n) {
             Cs = MPRES(rp,p,As,Bs);
             b = MPEMV(1,p,D,i);
             b = MDINV(p,b);
             C = MPINT(p,D,i,b,rp,C,Cs);
             Dp = LIST4(1,1,0,p - i);
             D = MPPROD(1,p,D,Dp);
             if (PDEG(D) > k)
               goto Return; } }
         i++; }

Step4: /* Algorithm fails. */
       FAIL("MPRES","Fails",r,p,A,B);

Return: /* Prepare for return. */
       return(C);
}

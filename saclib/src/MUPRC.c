/*======================================================================
                      MUPRC(p,A,B; C,r)

Modular univariate polynomial resultant and cofactor.

Inputs
   p : a BETA-digit, prime.
 A,B : in Z/(p)[X], A and B are of positive degree.

Outputs
  C  : in Z/(p)[X] such that for some D in Z/(p)[X], AD+BC = R.
  R  : in Z/(p), the resultant of A and B.
======================================================================*/
#include "saclib.h"

void MUPRC(p,A,B, C_,r_)
       Word p,A,B, *C_,*r_;
{
       Word A1,A2,A3,C,Q,i,n1,n2,n3,r,r2,s,t,v1,v2,v3;
       /* hide i,n1,n2,n3,r2,s,t; */

Step1: /* Initialize. */
       r = 1;
       A1 = A;
       A2 = B;
       v1 = 0;
       v2 = PMON(1,0);
       n1 = PDEG(A1);
       n2 = PDEG(A2);
       s = 1;
       if (n1 < n2)
         {
         if (ODD(n1) && ODD(n2))
           s = -s;
         t = A1;
         A1 = A2;
         A2 = t;
         v1 = v2;
         v2 = 0;
         }

Step2: /* Loop. */
       do
         {
         MPQR(1,p,A1,A2,&Q,&A3);
         v3 = MPDIF(1,p,v1,MPPROD(1,p,Q,v2));
         if (A3 == 0)
           {
           r = 0;
           C = v3;
           goto Return;
           }
         n1 = PDEG(A1);
         n2 = PDEG(A2);
         n3 = PDEG(A3);
         if (ODD(n1) && ODD(n2))
           s = -s;
         r2 = PLDCF(A2);
         for (i = 1; i <= n1 - n3; i++)
           r = MDPROD(p,r,r2);
         A1 = A2;
         A2 = A3;
         v1 = v2;
         v2 = v3;
         }
       while (!(n3 == 0));

Step3: /* Finish. */
       r2 = PLDCF(A2);
       for (i = 1; i <= n2 - 1; i++)
         r = MDPROD(p,r,r2);
       if (s == -1)
         r = p - r;
       C = MPMDP(1,p,r,v2);
       r = MDPROD(p,r,r2);

Return: /* Prepare for return. */
       *C_ = C;
       *r_ = r;
       return;
}

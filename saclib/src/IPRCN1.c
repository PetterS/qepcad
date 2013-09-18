/*======================================================================
                      J <- IPRCN1(A,I,s,k)

Integral polynomial real root calculation, 1 root.

Inputs
  A : in Z[X], positive, primitive, deg(A) > 0.
  I : an open standard interval (a1,a2) 
      with binary rational endpoints containing
      a unique root alpha of A and containing no roots of A' or A''.
      min(|A'(a1)|,|A'(a2)|) >= (3/4)max(|A'(a1)|,|A'(a2)|).
  s : a BETA-digit, is the sign of A' * A'' on I.
  k : a BETA-digit.

Outputs
  J : a subinterval of I of length 2^k or less containing alpha and with
      binary rational endpoints.
======================================================================*/
#include "saclib.h"

Word IPRCN1(A,I,s,k)
       Word A,I,s,k;
{
       Word Ap,J,b,b1,b2,d1,d2,dp,q1,q2;
       /* hide b; */

Step1: /* Initialize. */
       Ap = IPDMV(1,A);
       J = I;

Step2: /* Refine interval. */
       while (RILC(J,k) == 0)
         {
         FIRST2(J,&b1,&b2);
         d1 = IUPBRE(A,b1);
         d2 = IUPBRE(A,b2);
         if (s < 0)
           b = b1;
         else
           b = b2;
         dp = IUPBRE(Ap,b);
         q1 = RNQ(d1,dp);
         q2 = RNQ(d2,dp);
         b1 = RNDIF(b1,q1);
         b2 = RNDIF(b2,q2);
         J = LIST2(b1,b2);
         if (RNCOMP(b1,b2) == 0)
           goto Return;
         J = RINT(J);
         }

Return: /* Prepare for return. */
       return(J);
}

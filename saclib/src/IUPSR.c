/*===========================================================================
			    IUPSR(A,B; ab,bb,C)

Integral univariate polynomial semi-remainder.

Inputs
  A,B   : in Z[x], deg(A) >= deg (B) > 0.

Outputs
  ab,bb : in Z.
      C : in Z[x].
          Let m = deg(A), n = deg(B), k = m - n, a = ldcf(A),
          b = ldcf(B), d = gcd(a,b).
          Then ab = a/d, bb = b/d and C = bb * A - ab * x^k * B.
===========================================================================*/
#include "saclib.h"

void IUPSR(A,B, ab_,bb_,C_)
       Word A,B, *ab_,*bb_,*C_;
{
       Word Ab,Bb,C,C1,C2,a,ab,b,bb,d,k,m,n;

Step1: /* Get degrees and leading coefficients. */
       m = PDEG(A);
       n = PDEG(B);
       a = PLDCF(A);
       b = PLDCF(B);

Step2: /* Compute cofactors. */
       IGCDCF(a,b,&d,&ab,&bb);

Step3: /* Compute C(x). */
       k = m - n;
       Ab = PRED(A);
       Bb = PRED(B);
       C1 = IPIP(1,bb,Ab);
       C2 = IPPROD(1,LIST2(k,ab),Bb);
       C = IPDIF(1,C1,C2);

Return: /* Prepare for return. */
       *ab_ = ab;
       *bb_ = bb;
       *C_ = C;
       return;
}

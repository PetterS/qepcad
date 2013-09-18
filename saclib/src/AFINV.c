/*======================================================================
                      b <- AFINV(M,a)

Algebraic number field element inverse.

Inputs
 M : in Z[X], the minimal polynomial of an algebraic number alpha.
 a : in Q(alpha), not zero

Outputs
 b : in Q(alpha), the multiplicative inverse of a.
======================================================================*/
#include "saclib.h"

Word AFINV(M,a)
       Word M,a;
{
       Word A,B,R,b,r,s,s1,s2;

Step1: /* Decompose a. */
       FIRST2(a,&r,&A);

Step2: /* Trivial case. */
       if (PDEG(A) == 0)
         {
         r = RNINV(r);
         b = LIST2(r,A);
         goto Return;
         }

Step3: /* Compute resultant and cofactor. */
       IUPRC(M,A,&B,&R);
       if (R == 0)
         FAIL("AFINV","Resultant is 0",M,A,B);

Step4: /* Compute content and primitive part of cofactor. */
       IPSCPP(1,B,&s,&b,&B);
       if (s < 0)
         b = INEG(b);

Step5: /* Compute rational part of b. */
       s1 = RNINV(r);
       s2 = RNRED(b,R);
       s = RNPROD(s1,s2);

Step6: /* Compose b. */
       b = LIST2(s,B);

Return: /* Prepare for return. */
       return(b);
}

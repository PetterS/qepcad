/*===========================================================================
                           R <- RNFMR(M,Mp,m,u)

Rational number from modular residue.

Inputs
  M : in Z, M > 1, and M odd.
      [That M is odd is used in certain inequality tests.]
  Mp: in Z, Mp = floor((M/2)^(1/2)).
  m : a BETA-digit, m = ILOG2(Mp).
  U : in Z/(M).

Outputs
  R : in Q, or R = NIL.  If there exist integers A and B such that

                  (1) A = B U (mod M),
                  (2) 1 <= B < (M/2)^(1/2), |A| < (M/2)^(1/2), and 
                  (3) gcd(A,B) = gcd(B,M) = 1,

      then R = A / B; otherwise R = NIL.  If such A and B exist,
      they are unique.
===========================================================================*/
#include "saclib.h"

Word RNFMR(M,Mp,m,U)
       Word M,Mp,m,U;
{
       Word A,B,R;

Step1: /* Solve the congruence. */
       R = ISMC(M,Mp,m,U);
       if (R == NIL || R == 0)
          goto Return;

Step2: /* Check the denominator. */
       A = FIRST(R);
       B = SECOND(R);
       if (IGCD(A,B) != 1)
          R = NIL;

Return: /* Prepare for return. */
       return(R);
}

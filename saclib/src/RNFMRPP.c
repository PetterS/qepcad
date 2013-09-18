/*===========================================================================
                         R <- RNFMRPP(M,Mp,m,p,u)

Rational number from modular residue, modulus a power of a prime.

Inputs
  M : in Z, M  = p^k, for some k >= 1, and M odd.
      [That M is odd is used in certain inequality tests.]
  Mp: in Z, Mp = floor((M/2)^(1/2)).
  m : a BETA-digit, m = ILOG2(Mp).
  p : a BETA-digit, p prime, p < 2^15.
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
#define MAXB 200

Word RNFMRPP(M,Mp,m,p,U)
       Word M,Mp,m,p,U;
{
       Word B,Bp[MAXB],*Bt,R,o,n,s;

Step1: /* Solve the congruence. */
       R = ISMC(M,Mp,m,U);
       if (R == NIL || R == 0)
          goto Return;

Step2: /* Check the denominator. */
       B = SECOND(R);
       if (B < BETA) {
          if ((B % p) == 0)
             R = NIL; }
       else {
          IFLTA(B,Bp,MAXB,&Bt,&n,&s,&o);
          if (IHDREM(Bt,n,p) == 0)
             R = NIL;
          if (n > MAXB)
             FREEARRAY(Bt); }

Return: /* Prepare for return. */
       return(R);
}

/*==========================================================================
                      C <- MAFUPGCD(p,M,A,B);

Modular algebraic field univariate polynomial gcd.

Input
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x].
  A,B : in (Z/(p)[x])/(M)[y].

Output
  C : in (Z/(p)[x])/(M)[y].  If the last non-zero element in the 
      natural prs of A and B is invertible in (Z/(p)[x])/(M) then
      C is the monic gcd of A and B.  Otherwise C = NIL.
==========================================================================*/
#include "qepcad.h"

Word MAFUPGCD(Word p, Word M, Word A, Word B)
{
       Word C,A1,A2,A3,a,ap,r;
  
Step1: /* A = 0 \/ B = 0 */
       if (A == 0) {
	 C = MAFUPMON(p,M,B);
	 goto Return;
       }
       if (B == 0) {
	 C = MAFUPMON(p,M,A);
	 goto Return;
       }

Step2: /* Initialize. */
       if (PDEG(A) > PDEG(B)) {
	 A1 = A;
	 A2 = B;
       } else {
	 A1 = B;
	 A2 = A;
       }
      
Step3: /* Compute natural prs. */
       do {
	 A3 = MAFUPNR(p,M,A1,A2);
	 A1 = A2;
	 A2 = A3;
       } while (A2 != 0 && A2 != NIL);

Step4: /* Make gcd monic. */
       if (A2 != NIL)
	 C = MAFUPMON(p,M,A1);
       else
	 C = NIL;

Return: /* Prepare for return. */
       return(C);
}

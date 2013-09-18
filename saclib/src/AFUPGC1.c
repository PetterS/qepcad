/*===========================================================================
		    AFUPGC1(M,A,B; C,Ab,Bb)

Algebraic number field univariate polynomial greatest common divisor
and cofactors, degree 1.

Inputs
    M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A,B : in Q(alpha)[x], deg A = 1 or deg B = 1.

Outputs
      C : in Q(alpha)[x], C is a gcd of A and B.
 Ab, Bb : in Q(alpha)[x], the cofactors Ab = A / C and Bb = B / C.
===========================================================================*/
#include "saclib.h"

void AFUPGC1(M,A,B, C_,Ab_,Bb_)
       Word M,A,B,*C_,*Ab_,*Bb_;
{
       Word C,Ab,Bb,R;

Step1: /* Apply fast relative-primality test. */
       if (AFUPFRPT(M,A,B) == 1)
	  goto Step5;
	     
Step2: /* Both have degree 1. */
       if (PDEG(A) == 1 && PDEG(B) == 1)
	  if (EQUAL(PLDCF(A),AFFINT(1))) {
	     C = A;
	     AFUPQR(M,B,C,&Bb,&R);
	     if (R == 0) {
		Ab = PMON(PLDCF(A),0);
		goto Return; }
	     else
		goto Step5; }
	  else {
	     C = AFPMON(1,M,B);
	     AFUPQR(M,A,C,&Ab,&R);
	     if (R == 0) {
		Bb = PMON(PLDCF(B),0);
		goto Return; }
	     else
		goto Step5; }

Step3: /* deg A = 1. */
       if (PDEG(A) == 1) {
	  C = AFPMON(1,M,A);
	  AFUPQR(M,B,C,&Bb,&R);
	  if (R == 0) {
	     Ab = PMON(PLDCF(A),0);
	     goto Return; }
	  else
	     goto Step5; }

Step4: /* deg B = 1. */
       C = AFPMON(1,M,B);
       AFUPQR(M,A,C,&Ab,&R);
       if (R == 0) {
	  Bb = PMON(PLDCF(B),0);
	  goto Return; }
	     
Step5: /* Relatively prime. */
       C = PMON(AFFINT(1),0);
       Ab = A;
       Bb = B;

Return: /* Prepare for return. */
       *C_ = C;
       *Ab_ = Ab;
       *Bb_ = Bb;
       return;
}

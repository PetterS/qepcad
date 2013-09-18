/*===========================================================================
			 AMUPRINCS(M,I,A,a,b;L,Is)

Algebraic module univariate polynomial root isolation, 
normalized coefficient sign variation method.

Inputs
  M : an element of Z[X].  M(alpha) = 0.
  I : an isolating interval for alpha.
  A : an element of Z[alpha,X].  A /= 0 is squarefree.
  a,b :  binary rational numbers.

Outputs
  L : a list (I_1,...,I_k) of isolating intervals for the real roots of
      A(T(X)) in the interval (a,b) where T(X) is the linear transformation
      which maps (a,b) onto (-1,1).  I_j is either open or a one-point
      interval, and is a subinterval of (a,b).  I_1 < ... < I_k.
  Is : Refined acceptable isolating interval for alpha.
===========================================================================*/
#include "saclib.h"

void AMUPRINCS(M,I,A,a,b,L_,Is_)

       Word M,I,A,a,b;
       Word *L_,*Is_;
{
       Word L,Is;
       Word As,A_1,A_2,Ab,L_0,L_1,L_2,c,m,v;

Step1: /* Check if A(a) = 0 and Initialize. */
       m = PDEG(A);
       Ab = PDBORD(A);
       Is = I;
       if (PDEG(Ab) < m)
	  L_0 = LIST1(LIST2(a,a));
       else
	  L_0 = NIL;

Step2: /* Base case. */
       As = AMUPTR1(PRT(Ab));
       AMUPVARIR(M,Is,As,&v,&Is);
       if (v == 0) {
	  L = L_0;
	  goto Return; }
       else
	  if (v == 1) {
	     L = CONC(L_0,LIST1(LIST2(a,b)));
	     goto Return; }
	  else {
	     c = RNQ(RNSUM(a,b),RNINT(2));
	     A_1 = AMUPBHT(Ab,-1);
	     A_2 = AMUPTR1(A_1); }

Step3: /* Left recursive call. */
       AMUPRINCS(M,Is,A_1,a,c,&L_1,&Is);

Step4: /* Right recursive call. */
       AMUPRINCS(M,Is,A_2,c,b,&L_2,&Is);

Step5: /* Combine intervals. */
       L = CONC(L_0,CONC(L_1,L_2));

Return: /* Prepare for return. */
       *L_ = L;
       *Is_ = Is;
       return;
}

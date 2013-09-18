/*===========================================================================
			IUPFAC(A; s,c,L)

Integral univariate polynomial factorization.

Inputs
  A : in Z[x], A non-zero.

Outputs
  s : a BETA-digit, s = sign(A).
  c : in Z, c = cont(A).
  L : a list ((e_1,A_1),...,(e_k,A_k)), k >= 0, with e_i in Z, e_i > 0,
      e_1 <= e_2 <= ... <= e_k,  A_i in Z[x], A_i irreducible,
      positive, and A = s * c * A_1^e_1 * ... * A_k^e_k.
===========================================================================*/
#include "saclib.h"

void IUPFAC(A, s_,c_,L_)
       Word A, *s_,*c_,*L_;
{
       Word A1,Ab,L,L1,P,S,c,e1,n,s;

Step1: /* Compute sign, content and primitive part. */
       IPSCPP(1,A,&s,&c,&Ab);

Step2: /* Degree 0. */
       n = PDEG(A);
       if (n == 0) {
	  L = NIL;
	  goto Return; }

Step3: /* Degree 1. */
       if (n == 1) {
	  L = LIST1(LIST2(1,Ab));
	  goto Return; }

Step4: /* Degree 2. */
       if (n == 2) {
	  L = IPPFAC2(1,Ab);
	  goto Return; }

Step5: /* Compute squarefree factorization. */
       S = IPSF(1,Ab);

Step6: /* Factor squarefree factors */
       S = INV(S);
       L = NIL;
       do {
	  ADV(S,&P,&S);
	  FIRST2(P,&e1,&A1);
	  L1 = IUSFPF(A1);
	  do {
	     ADV(L1,&A1,&L1);
	     L = COMP(LIST2(e1,A1),L); }
	  while (L1 != NIL); }
       while (S != NIL);

Return: /* Prepare for return. */
       *s_ = s;
       *c_ = c;
       *L_ = L;
       return;
}

/*=======================================================================
                        AINQ(A,B,Q,R,S,T)

Array integer nearest quotient.

Inputs
   A, B : array integers, with B /= 0.
   Q, R, S,T : arrays.  Let m = L(A), n = L(B).  The size of Q must
      be at least m - n + 3 and at least 3.  The sizes of R and S
      must be at least m + 3.  The size of T must be at least n + 2.

Effect
   {A / B}, the nearest integer to A / B, is placed in the arraay Q.
========================================================================*/
#include "saclib.h"

void AINQ(A,B,Q,R,S,T)
	BDigit *A,*B,*Q,*R,*S,*T;
{
	BDigit c,i,k,s,t;

Word Ap,Bp,Qp,Rp;

Step1: /* Apply AIQR. */
	AIQR(A,B,Q,R,T);

Step2: /* If |R| > |B / 2|, add 1 to |Q|. */
	if (R[0] == 0)
	   goto Return;
	R[0] = 1;
	AIMP2(R,1,S);
	s = B[0];
	B[0] = 1;
	t = AICOMP(S,B);
	B[0] = s;
	if (t < 0)
	   goto Return;
	if (Q[0] == 0) {
	   if (A[0] == B[0])
	      Q[0] = 1;
	   else
	      Q[0] = -1;
	   Q[1] = 1;
	   Q[2] = 1;
	   goto Return; }
	k = Q[1];
	i = 2;
	do {
	   c = Q[i] + 1;
	   Q[i] = c & BETA1;
	   c = c >> ZETA;
	   i = i + 1; }
	while (c == 1 && i <= k + 1);
	if (c == 1 && i > k + 1) {
	   Q[i] = 1;
	   Q[1] = k + 1; }
	   
Return: /* Return. */
	return;
}

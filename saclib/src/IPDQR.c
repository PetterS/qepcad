/*===========================================================================
			     IPDQR(r,A,m; Q,R)

Integral polynomial digit quotient and remainder.

Inputs
  r : a BETA-digit, r >= 0.
  A : in Z[x_1,...,x_r].  All base coefficients of A are non-negative.
  m : a BETA-digit, m >= 2.

Outputs
  Q : in Z[x_1,...,x_r].  All base coefficients of Q are non-negative.
  R : in Z/(m)[x_1,...,x_r].
  Q and R satisfy A = m Q + R.
===========================================================================*/
#include "saclib.h"

void IPDQR(r,A,m,Q_,R_)
       Word r,A,m,*Q_,*R_;
{
       Word Ap,A1,e,Q,Q1,R,R1,rp;

Step1: /* A = 0. */
       if (A == 0) {
	  Q = 0;
	  R = 0;
	  goto Return; }

Step2: /* r = 0. */
       if (r == 0) {
	  IQR(A,m,&Q,&R);
	  goto Return; }

Step3: /* Loop though the coefficients. */
       Ap = A;
       Q = R = NIL;
       rp = r - 1;
       do {
	  A1 = PLDCF(Ap);
	  e = PDEG(Ap);
	  IPDQR(rp,A1,m,&Q1,&R1);
	  if (Q1 != 0)
	     Q = COMP2(Q1,e,Q);
	  if (R1 != 0)
	     R = COMP2(R1,e,R);
	  Ap = PRED(Ap); }
       while (Ap != 0);

Step4: /* Clean up. */
       if (Q == NIL)
	  Q = 0;
       else
	  Q = INV(Q);
       if (R == NIL)
	  R = 0;
       else
	  R = INV(R);

Return: /* Prepare for return. */
       *Q_ = Q;
       *R_ = R;
}

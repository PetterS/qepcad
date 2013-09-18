/*===========================================================================
		       IPDQNR(r,A,m; Q,R)

Integral polynomial digit quotient and non-negative remainder.

Inputs
  r : a BETA-digit, r >= 0.
  A : in Z[x_1,...,x_r].
  m : a BETA-digit, m >= 2.

Outputs
  Q : in Z[x_1,...,x_r].
  R : in Z[x_1,...,x_r].
  Q and R satisfy A = m Q + R.  Each coefficient of R is in [0,...,m-1].
===========================================================================*/
#include "saclib.h"

void IPDQNR(r,A,m,Q_,R_)
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
	  IDQR(A,m,&Q,&R);
	  if (R < 0) {
	     R = m + R;
	     Q = IDIF(Q,1); }
	  goto Return; }

Step3: /* Loop though the coefficients. */
       Ap = A;
       Q = R = NIL;
       rp = r - 1;
       do {
	  A1 = PLDCF(Ap);
	  e = PDEG(Ap);
	  IPDQNR(rp,A1,m,&Q1,&R1);
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

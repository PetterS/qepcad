/*===========================================================================
			      RPQR(r,A,B; Q,R)

Rational polynomial quotient and remainder.

Inputs
  A, B : in Q[x_1,...,x_r], B non-zero.
  r    : a BETA-digit, r >= 1.

Outputs
  Q,R : in Q[x_1,...,x_r], the unique rational polynomials such that
        either B divides A, Q = A / B and R = 0 or else
        B does not divide A and A = B Q + R with deg(R) minimal.
===========================================================================*/
#include "saclib.h"

void RPQR(r,A,B, Q_,R_)
       Word r,A,B, *Q_,*R_;
{
       Word Bp,Q,Q1,Qp,R,Rp,a,b,d,m,n,q,rp,s;

Step1: /* Initialize. */
       n = PDEG(B);
       b = PLDCF(B);
       Bp = PRED(B);
       Q = NIL;
       R = A;
       rp = r - 1;

Step2: /* Compute quotient terms. */
       while (R != 0) {
	  m = PDEG(R);
	  d = m - n;
	  if (d < 0)
	     goto Step3;
	  a = PLDCF(R);
	  if (rp == 0) {
	     q = RNQ(a,b);
	     s = 0; }
	  else
	     RPQR(rp,a,b,&q,&s);
	  if (s != 0)
	     goto Step3;
	  Q = COMP2(q,d,Q);
	  Q1 = LIST2(d,q);
	  Rp = PRED(R);
	  Qp = RPPROD(r,Bp,Q1);
	  R = RPDIF(r,Rp,Qp); }

Step3: /* Finish. */
       if (Q == NIL)
	  Q = 0;
       else
	  Q = INV(Q);

Return: /* Prepare for return. */
       *Q_ = Q;
       *R_ = R;
       return;
}

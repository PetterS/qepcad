/*===========================================================================
		       AFUPQR(M,A,B; Q,R)

Algebraic number field univariate polynomial quotient and remainder.  

Inputs
    M : in Z[x], the minimal polynomial of an algebraic number alpha.
  A,B : in Q(alpha)[y], B != 0.

Outputs
  Q,R : in Q(alpha)[y].
        If B divides A, then Q = B / A and R = 0.  Otherwise,
        Q and R are the unique algebraic number field univariate
	polynomials such that A = B*Q+R, with deg(R) minimal.
===========================================================================*/
#include "saclib.h"

void AFUPQR(M,A,B, Q_,R_)
       Word M,A,B, *Q_,*R_;
{
       Word Bp,Q,Q1,Qp,R,Rp,a,b,bp,d,m,n,q,s;

Step1: /* Initialize. */
       n = PDEG(B);
       b = PLDCF(B);
       Bp = PRED(B);
       Q = NIL;
       R = A;
       bp = AFINV(M,b);

Step2: /* Compute quotient terms. */
       while (R != 0) {
	  m = PDEG(R);
	  d = m - n;
	  if (d < 0)
	     goto Step3;
	  a = PLDCF(R);
	  q = AFPROD(M,a,bp);
	  s = 0;
	  if (s != 0)
	     goto Step3;
	  Q = COMP2(q,d,Q);
	  Q1 = LIST2(d,q);
	  Rp = PRED(R);
	  Qp = AFPPR(1,M,Bp,Q1);
	  R = AFPDIF(1,Rp,Qp); }

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

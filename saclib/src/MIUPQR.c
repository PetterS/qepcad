/*===========================================================================
                         MIUPQR(M,A,B; Q,R)

Modular integral univariate polynomial quotient and remainder.

Inputs
  M   : in Z, M > 0.
  A,B : in Z/(M)[X] with ldcf(B) a unit.

Outputs
  Q,R : in Z/(M)[X], the unique elements such that 
        A = B Q + R with either R=0 or deg(R) < deg(B).
===========================================================================*/
#include "saclib.h"

void MIUPQR(M,A,B, Q_,R_)
       Word M,A,B, *Q_,*R_;
{
       Word Bp,Q,Q1,Qp,R,Rp,a,b,bp,d,m,n,q;

Step1: /* Initialize. */
       n = PDEG(B);
       b = PLDCF(B);
       Bp = PRED(B);
       Q = NIL;
       R = A;
       bp = MIINV(M,b);

Step2: /* Compute quotient terms. */
       while (R != 0) {
	  m = PDEG(R);
	  d = m - n;
	  if (d < 0)
	     goto Step3;
	  a = PLDCF(R);
	  q = MIPROD(M,a,bp);
	  Q = COMP2(q,d,Q);
	  Q1 = LIST2(d,q);
	  Rp = PRED(R);
	  Qp = MIPPR(1,M,Bp,Q1);
	  R = MIPDIF(1,M,Rp,Qp); }

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

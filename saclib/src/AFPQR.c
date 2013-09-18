/*==========================================================================
                      AFPQR(r,M,A,B; Q,R)

Algebraic number field polynomial quotient and remainder.  

Inputs
    r : a BETA-digit, r >= 1.
    M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A,B : in Q(alpha)[X1,...,Xr], B not zero.

Outputs
  Q,R : in Q(alpha)[X1,...,Xr].
        Q and R are the unique algebraic number field polynomials
        such that either B divides A, Q = A / B, and R = 0 or else B
        does not divide A and A = BQ+R with degree(R) minimal.
==========================================================================*/
#include "saclib.h"

void AFPQR(r,M,A,B, Q_,R_)
       Word r,M,A,B, *Q_,*R_;
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
           q = AFQ(M,a,b);
           s = 0;
	 } else
           AFPQR(rp,M,a,b,&q,&s);
         if (s != 0)
           goto Step3;
         Q = COMP2(q,d,Q);
         Q1 = LIST2(d,q);
         Rp = PRED(R);
         Qp = AFPPR(r,M,Bp,Q1);
         R = AFPDIF(r,Rp,Qp);
       }

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

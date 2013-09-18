/*======================================================================
                      IPQR(r,A,B; Q,R)

Integral polynomial quotient and remainder.

Inputs
  r : a BETA-digit, r >= 1, the number of variables.
  A , B : in Z[X1,...,Xr], B non-zero.

Outputs
  Q, R : in Z[X1,...,Xr].
	 If B divides A then Q=A/B and R=0 
	 else  A=BQ+R with deg(R) minimal.
	 Q and R are uniquely determined if R=0 or
	 deg(R) < deg(B).
======================================================================*/
#include "saclib.h"

void IPQR(r,A,B, Q_,R_)
       Word r,A,B, *Q_,*R_;
{
       Word Bp,Q,Q1,Qp,R,Rp,a,b,d,m,n,q,rp,s;
       /* hide Rp,a,d,m,n,rp; */

Step1: /* Initialize. */
       n = PDEG(B);
       b = PLDCF(B);
       Bp = PRED(B);
       Q = NIL;
       R = A;
       rp = r - 1;

Step2: /* Compute quotient terms. */
       while (R != 0)
         {
         m = PDEG(R);
         d = m - n;
         if (d < 0)
           goto Step3;
         a = PLDCF(R);
         if (rp == 0)
           IQR(a,b,&q,&s);
         else
           IPQR(rp,a,b,&q,&s);
         if (s != 0)
           goto Step3;
         Q = COMP2(q,d,Q);
         Q1 = LIST2(d,q);
         Rp = PRED(R);
         Qp = IPPROD(r,Bp,Q1);
         R = IPDIF(r,Rp,Qp);
         }

Step3: /* Finish. */
       if (Q == NIL)
         Q = 0;
       else
         Q = INV(Q);
       goto Return;

Return: /* Prepare for return. */
       *Q_ = Q;
       *R_ = R;
       return;
}

/*======================================================================
                      MPQR(r,p,A,B; Q,R)

Modular polynomial quotient and remainder.

Inputs
  A,B : in Z/(p)[X1,...,Xr], B non-zero.
  r : a BETA-digit, r >= 1, the number of variables.
  p : a prime BETA-digit.

Outputs
  Q,R : in Z/(p)[X1,...,Xr], the unique polynomials such that 
        either B divides A, Q=A/B  and R=0 or else B does not 
        divide A and A=BQ+R with deg(R) minimal.
======================================================================*/
#include "saclib.h"

void MPQR(r,p,A,B, Q_,R_)
       Word r,p,A,B, *Q_,*R_;
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
       while (R != 0) {
         m = PDEG(R);
         d = m - n;
         if (d < 0)
           goto Step3;
         a = PLDCF(R);
         if (rp == 0) {
           q = MDQ(p,a,b);
           s = 0; }
         else
           MPQR(rp,p,a,b,&q,&s);
         if (s != 0)
           goto Step3;
         Q = COMP2(q,d,Q);
         Q1 = LIST2(d,q);
         Rp = PRED(R);
         Qp = MPPROD(r,p,Bp,Q1);
         R = MPDIF(r,p,Rp,Qp); }

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

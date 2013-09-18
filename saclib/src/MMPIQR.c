/*============================================================================
                      MMPIQR(r,M,D,A,B; Q,R)

Modular monic polynomial mod ideal quotient and remainder.

Inputs
  M : in Z, M > 0.
  D : a list (d_1,...,d_{r-1}) of non-negative BETA-digits.
  r : a BETA-digit, r >= 1.
  A,B : in (Z/(M))[X_1,...,X_{r-1},Y] / (X_1^d_1,...,X_{r-1}^d_{r-1}),
  with B monic.
  
Outputs
  Q,R : in (Z/(M))[X_1,...,X_{r-1},Y] / (X_1^d_1,...,X_{r-1}^d_{r-1}). 
  If B divides A then Q = A / B and R = 0.
        Otherwise A = B * Q + R with deg_y(R) < deg_y(B).
============================================================================*/
#include "saclib.h"

void MMPIQR(r,M,D,A,B, Q_,R_)
       Word r,M,D,A,B, *Q_,*R_;
{
       Word Bp,Q,Q1,Qp,R,Rp,a,d,m,n;

Step1: /* Initialize. */
       n = PDEG(B);
       Bp = PRED(B);
       Q = NIL;
       R = A;

Step2: /* Compute quotient terms. */
       while (R != 0) {
         m = PDEG(R);
         d = m - n;
         if (d < 0)
           goto Step3;
         a = PLDCF(R);
         Q = COMP2(a,d,Q);
         Q1 = LIST2(d,a);
         Rp = PRED(R);
         Qp = MIPIPR(r,M,D,Bp,Q1);
         R = MIPDIF(r,M,Rp,Qp);
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

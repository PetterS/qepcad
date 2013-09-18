/*===========================================================================
                               GINQR(A,B; Q,R)

Gaussian integer nearest quotient and remainder.  

Inputs
  A, B  : Gaussian integers, B /= 0.  

Outputs
  Q     : the nearest Gaussian integer to A/B; if several are
          equally near to A/B, Q is the one nearest to the origin.
  R     : the corresponding remainder, A - B * Q.
===========================================================================*/
#include "saclib.h"

void GINQR(A,B, Q_,R_)
       Word A,B, *Q_,*R_;
{
        Word A1,A2,B1,B2,N,P,P1,P2,Q,Q1,Q2,R,R1,R2;

Step1: /* A = 0. */
        if (A == 0) {
           Q = 0;
           R = 0;
           goto Return; }

Step2: /* B real or imaginary. */
        FIRST2(B,&B1,&B2);
        if (B1 != 0 && B2 != 0)
           goto Step3;
        FIRST2(A,&A1,&A2);
        if (B2 == 0) {
           INQR(A1,B1,&Q1,&R1);
           INQR(A2,B1,&Q2,&R2); }
        else {
           INQR(A2,B2,&Q1,&R2);
           INQR(A1,INEG(B2),&Q2,&R1); }
        Q = GIFP(Q1,Q2);
        R = GIFP(R1,R2);
        goto Return;
        
Step3: /* Compute N = norm(B) and P  = A * conj(B). */
        N = GINORM(B);
        P = GIPROD(A,GICONJ(B));

Step4: /* Compute the nearest Gaussian integer, Q, to P / N. */
        FIRST2(P,&P1,&P2);
        INQR(P1,N,&Q1,&R1);
        INQR(P2,N,&Q2,&R2);
        Q = GIFP(Q1,Q2);

Step5: /* Compute the remainder R = A - B * Q. */
        R = GIDIF(A,GIPROD(B,Q));

Return: /* Return Q and R. */
        *Q_ = Q;
        *R_ = R;
        return;
}

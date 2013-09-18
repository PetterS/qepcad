/*===========================================================================
                               INQR(A,B; Q,R)

Integer nearest quotient and remainder.  

Inputs
  A, B  : Integers, B /= 0.  

Outputs
  Q     : the nearest integer to A/B; if two integers are
          equally near to A/B, Q is the one nearest to 0.
  R     : the corresponding remainder, A - B * Q.
===========================================================================*/
#include "saclib.h"

void INQR(A,B, Q_,R_)
       Word A,B, *Q_,*R_;
{
        Word Q,R,s,t,u;
Step1: /* Compute the usual quotient and remainder. */
        IQR(A,B,&Q,&R);

Step2: /* Remainder zero. */
        if (R == 0)
           goto Return;

Step3: /* Compute signs of A and B. */
        s = ISIGNF(A);
        t = ISIGNF(B);

Step4: /* A and  positive. */
        if (s > 0 && t > 0) {
           u = ICOMP(B,IDPR(R,2));
           if (u < 0) {
              Q = ISUM(Q,1);
              R = IDIF(R,B); }
           goto Return; }

Step5: /* A and B negative. */
        if (s < 0 && t < 0) {
           u = ICOMP(B,IDPR(R,2));
           if (u > 0) {
              Q = ISUM(Q,1);
              R = IDIF(R,B); }
           goto Return; }

Step6: /* A positive and B negative. */
        if (s > 0 && t < 0) {
           u = ICOMP(B,IDPR(R,-2));
           if (u > 0) {
              Q = ISUM(Q,-1);
              R = ISUM(R,B); }
           goto Return; }

Step7: /* A negative and B positive. */
        if (s < 0 && t > 0) {
           u = ICOMP(B,IDPR(R,-2));
           if (u < 0) {
              Q = ISUM(Q,-1);
              R = ISUM(R,B); }
           goto Return; }

Return: /* Return Q and  R. */
        *Q_ = Q;
        *R_ = R;
        return;
}

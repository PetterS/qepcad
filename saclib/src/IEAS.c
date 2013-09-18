/*===========================================================================
			     IEAS(A1,m1,A2,m2; m1p)

Integer Euclidean algorithm step.

Inputs
  A1, A2: in Z, in array representation, with A1 >= A2 > 0.
  m1, m2: BETA digits, the lengths of A1 and A2, respectively.

Output
  m1p: the length in BETA-digits of A1 - floor(A1/A2) * A2.

Side effects
  A1 is replaced by A1 - floor(A1/A2) * A2.
===========================================================================*/
#include "saclib.h"

void IEAS(A1,m1,A2,m2, m1p_)
       Word *A1,m1,*A2,m2, *m1p_;
{
       Word *Q,m1p,q;

Step1: /* Compute quotient and remainder. */
       Q = GETARRAY(m1 - m2 + 1);
       IQRA(A1,m1,A2,m2,Q,&m1p,&q);

Step2: /* Free quotient array. */
       FREEARRAY(Q);

Return: /* Prepare for return. */
       *m1p_ = m1p;
       return;
}

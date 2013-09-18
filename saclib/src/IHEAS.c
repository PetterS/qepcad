/*===========================================================================
		  IHEAS(A1,m1,A2,m2,V1,n1,V2,n2; mp,np)

Integer half-extended Euclidean algorithm step.

Inputs
  A1, A2, V1, V2: in Z, in array representation, A1 >= A2 > 0.
  m1, m2, n1, n2: BETA digits, the lengths of A1, A2, V1, V2, respectively.

Outputs
  mp, np: BETA-digits.
          Let Q = floor(A1/A2).  Then mp is the length in BETA-digits of
	  A1 - Q A2, and np is the length in BETA-digits of V1 - Q V2.

Side effects
  A1 is replaced by A1 - Q A2, and
  V1 is replaced by V1 - Q V2.
===========================================================================*/
#include "saclib.h"

void IHEAS(A1,m1,A2,m2,V1,n1,V2,n2, mp_,np_)
       Word *A1,m1,*A2,m2,*V1,n1,*V2,n2, *mp_,*np_;
{
       Word *P,*Q,mp,np,p,q,s;

Step1: /* Compute quotient and remainder. */
       Q = GETARRAY(m1 - m2 + 1);
       IQRA(A1,m1,A2,m2,Q,&mp,&q);

Step2: /* Compute new V. */
       if (ISIGNA(V2,n2) < 0) {
	  s = -1;
	  INEGA(V2,n2); }
       else
	  s = 1;
       p = n2 + q;
       P = GETARRAY(p);
       IPRODA(V2,n2,Q,q,P);
       while (P[p-1] == 0 && p > 1)
	  p--;
       if (s == -1) {
	  INEGA(V2,n2);
	  INEGA(P,p); }
       IDIFA(V1,n1,P,p,&np);

Step3: /* Free arrays. */
       FREEARRAY(Q);
       FREEARRAY(P);

Return: /* Prepare for return. */
       *mp_ = mp;
       *np_ = np;
       return;
}

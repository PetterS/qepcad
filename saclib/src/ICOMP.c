/*===========================================================================
			      s <- ICOMP(A,B)

Integer comparison.

Inputs
  A, B : in Z.

Outputs
  s = sign(A-B).
===========================================================================*/
#include "saclib.h"

Word ICOMP(A,B)
       Word A,B;
{
       Word Ap,Bp,a,b,d,s,u,v;

Step1: /* A and B single-precision. */
       if (A < BETA && B < BETA) {
	  s = SIGN(A - B);
	  goto Return; }

Step2: /* A single-precision. */
       if (A < BETA) {
	  s = -ISIGNF(B);
	  goto Return; }

Step3: /* B single-precision. */
       if (B < BETA) {
	  s = ISIGNF(A);
	  goto Return; }

Step4: /* Compare corresponding digits. */
       s = 0;
       Ap = A;
       Bp = B;
       do {
	  ADV(Ap,&a,&Ap);
	  ADV(Bp,&b,&Bp);
	  u = SIGN(a);
	  v = SIGN(b);
	  if (u * v == -1) {
	     s = u;
	     goto Return; }
	  d = a - b;
	  if (d != 0)
	     s = SIGN(d); }
       while (Ap != NIL && Bp != NIL);

Step5: /* Same length */
       if (Ap == NIL && Bp == NIL)
	  goto Return;

Step6: /* Use sign of longer input. */
       if (Ap == NIL)
	  s = -ISIGNF(Bp);
       else
	  s = ISIGNF(Ap);

Return: /* Prepare for return. */
       return(s);
}

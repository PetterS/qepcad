/*===========================================================================
			       IMPB(A,n; B,t)

Integer multiplication by power of BETA.

Inputs
  A : in Z.
  n : a BETA-integer.

Outputs          
  B : the integral part of A * BETA^n.
  t : in {0,1,2,3}.  Truncation indicator.
      t = 0 if |A * BETA^n - B| = 0.
      t = 1 if |A * BETA^n - B| < 1/2.
      t = 2 if |A * BETA^n - B| = 1/2.
      t = 3 if |A * BETA^n - B| > 1/2.
===========================================================================*/
#include "saclib.h"

void IMPB(A,n, B_,t_)
       Word A,n,*B_,*t_;
{
       Word b,i,t,tp;
       Word B,L;

Step1: /* A=0 or n=0. */
       if (A == 0 || n == 0) {
	  B = A;
	  t = 0;
	  goto Return; }
       if (n < 0)
	  goto Step4;

Step2: /* n > 0. */
       B = AVAIL;
       L = B;
       for (i = 1; i < n; i++) {
	  if (L == NIL)
	     goto Step3;
	  L = RED(L); }
       if (L == NIL)
	  goto Step3;
       if (A < BETA) {
	  L = RED(L);
	  if (L == NIL)
	     goto Step3;
	  AVAIL = RED(L);
	  SRED(L,NIL);
	  SFIRST(L,A); }
       else {
	  AVAIL = RED(L);
	  SRED(L,A); }
       t = 0;
       goto Return;

Step3: /* Collect garbage and retry Step2. */
       GC();
       goto Step2;

Step4: /* n < 0. */
       if (A < BETA)
	  B = LIST1(A);
       else
	  B = A;
       tp = 0;
       i = 0;
       while (!ISNIL(B) && i != -n-1) {
	  ADV(B,&b,&B);
	  if (b != 0)
	     tp = 1;
	  i = i + 1; }
       if (B == NIL) {
	  B = 0;
	  t = tp;
	  goto Return; }
       ADV(B,&b,&B);
       if (b == 0 && tp == 0)
	  t = 0;
       else {
	  b = absm(b);
	  if (b < BETA/2)
	     t = 1;
	  else if (b > BETA/2)
	     t = 3;
	  else if (tp == 0)
	     t = 2;
	  else
	     t = 3; }
       if (B == NIL)
	  B = 0;
       else if (RED(B) == NIL)
	  B = FIRST(B);

Return: /* Prepare for return. */
       *B_ = B;
       *t_ = t;
       return;
}

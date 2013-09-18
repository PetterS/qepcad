/*===========================================================================
			       B <- IDP2(A,k)

Integer division by power of 2.

Inputs
  A  : in Z.
  k  : a non-negative BETA-digit.

Outputs
  B  : the integral part of A/2^k.
===========================================================================*/
#include "saclib.h"

Word IDP2(A,k)
       Word A,k;
{
       Word B,Ap,*As,a,ap,app,i,M,m,n,np,s;

Step1: /* A=0 or k=0. */
       if (A == 0 || k == 0) {
	  B = A;
	  goto Return; }

Step2: /* A single-precision. */
       if (A < BETA) {
	  if (k >= ZETA)
	     B = 0;
	  else {
	     if (A > 0)
		B = A >> k;
	     else 
		B = - (- A >> k); }
	  goto Return; }

Step3: /* Reduce to the case k < ZETA. */
       Ap = A;
       n = k;
       while (n >= ZETA && Ap != NIL) {
	  Ap = RED(Ap);
	  n = n - ZETA; }
       if (Ap == NIL) {
	  B = 0;
	  goto Return; }
       if (n == 0) {
	  if (RED(Ap) == NIL)
	     B = FIRST(Ap);
	  else
	     B = Ap; 
	  goto Return; }

Step4: /* Ap single-precision. */
       if (RED(Ap) == NIL) {
	  a = FIRST(Ap);
	  if (a < 0)
	     B = - ((-a) >> n);
	  else
	     B = a >> n;
	  goto Return; }
	
Step5: /* Put A' into array and get sign. */
       m = LENGTH(Ap);
       As = GETARRAY(m);
       for (i = 0; i < m; i++) {
	  As[i] = FIRST(Ap);
	  Ap = RED(Ap); }
       s = As[m - 1];

Step6: /* Shift right n bits. */
       np = ZETA - n;
       M = (01 << n) - 1;
       if (s > 0) {
	  ap = As[0] >> n;
	  for (i = 1; i < m; i++) {
	     app = (As[i] & M) << np;
	     As[i - 1] = ap | app;
	     ap = As[i] >> n; }
	  As[m - 1] = ap; }
       else {
	  ap = (- As[0]) >> n;
	  for (i = 1; i < m; i++) {
	     app = ((- As[i]) & M) << np;
	     As[i - 1] = -(ap | app);
	     ap = -(As[i]) >> n; }
	  As[m - 1] = - ap; }

Step7: /* Transfer result to a list. */
       B = IFATL(As,m,1);

Step8: /* Return array. */
       FREEARRAY(As);

Return: /* Prepare for return. */
       return(B);
}

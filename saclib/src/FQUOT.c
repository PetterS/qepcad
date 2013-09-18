/*======================================================================
			FQUOT(A,B,d,C)

Floating-point quotient.

Inputs
   A, B : floating-point numbers of the same precision, p. 
	  B is nonzero.
   d : a sign (rounding direction).
   C : an array of size at least 2 * p + 6.

Effect
   A / B is computed with p-precision arithmetic, rounded
   according to d, and the result is placed in the array C.
======================================================================*/
#include "saclib.h"

void FQUOT(A,B,d,C)
	BDigit *A,*B,d,*C;
{
	BDigit e,i,p,s,t,u,v;
	Word a,b,q,r,rs;

Step1: /* Get precision. */
	p = A[2];

Step2: /* A = 0? */
	if (A[1] == 0) {
	   C[0] = 0;
	   C[1] = 0;
	   C[2] = p;
	   goto Return; }

Step3: /* Convert mantissas to integers, a and b. */
	if (p == 1)
	   a = A[3];
	else {
	   a = NIL;
	   for (i = p + 2; i >= 3; i--) 
	      a = COMP(A[i],a); }
	if (p == 1)
           b = B[3];
        else {
           b = NIL;
           for (i = p + 2; i >= 3; i--)
              b = COMP(B[i],b); }

Step4: /* Make b to be greater than a. */
	t = ICOMP(a,b);
	if (t >= 0) {
	   b = IMP2(b,1);
	   u = 1; }
	else
	   u = 0;

Step5: /* Multiply a by BETA^p. */
	if (p == 1)
	   a = LIST1(a);
	for (i = 1; i <= p; i++)
	   a = COMP(0,a);
	   
Step6: /* Let a = q b + r, r >= 0. */
	IQR(a,b, &q,&r);

Step7: /* Compute the sign, s, of C. */
	if (A[1] == B[1])
	   s = 1;
	else
	   s = -1;
	C[1] = s;
	   
Step8: /* Round. */
	if (r != 0) {
	   if (d != 0) {
	      if (s == d)
	         q = ISUM(q,1); }
	   else {
	      rs = IMP2(r,1);
	      v = ICOMP(rs,b);
	      if (v == 0) {
	         if (IODD(q))
	            q = ISUM(q,1); }
	      else if (v  > 0)
	         q = ISUM(q,1); } }

Step9: /* q > BETA^p? */
	if (q > BETA && LENGTH(q) > p) {
	      q = IDP2(q,1);
	      u = u + 1; }
	
Step10: /* Compute and store exponent of C. */
	e = A[0] - B[0] + u;
	C[0] = e;

Step11: /* Store the precision of C. */
	C[2] = p;
	
Step12: /* Store mantissa of c. */
	if (p == 1)
	   C[3] = q;
	else {
	   for (i = 3; i <= p + 2; i++) {
	      C[i] = FIRST(q);
	      q = RED(q); } }

Return: /* Return. */
	return;
}

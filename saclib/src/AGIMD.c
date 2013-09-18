/*=======================================================================
                             AGIMD(A,B,C)

Array Gaussian integer minimal difference.

Inputs
   A, B :  nonzero array Gaussian integers with |A| >= |B|,
           approximately.
   C : a Gaussian integer array large enough for A - u * B, 
       where u is any unit.

Effect
   Let u be a unit that minimizes norm(A - u * B).  Then
   A - v * B is placed in C, where either v = u or else
   v is another unit and norm(A - v * B) = (1 + e) * norm(A - u * b)
   with |e| < 2^{-8}.
=======================================================================*/
#include "saclib.h"

void AGIMD(A,B,C)
        BDigit **A,**B,**C;
{
	BDigit a1,a2,b1,b2,c,cp,h1,h2,k,n,q,qp,q1,q2,t;

Step1: /* Obtain the quadrants and half-quadrants. */
	AGIQHQ(A, &q1,&h1);
        AGIQHQ(B, &q2,&h2);

Step2: /* If the half-quadrants are the same, compute a
          rotated sum. */
	q = q1 - q2 + 2;
	if (q < 0)
	   q = q + 4;
	else if (q > 3)
	   q = q - 4;
	if (h1 == h2) {
           AGIRSUM(A,B,q,C);
	   goto Return; }

Step3: /* Otherwise, decide among two rotations. */
	AGIBL(A, &n,&k);
	k = k - 10;
	if (k < 0) {
	   k = k + ZETA;
	   n = n - 1; }
	if (n < 0) {
	   n = 0;
	   k = 0; }
	a1 = AITRS(A[0],n,k);
        a2 = AITRS(A[1],n,k);
        b1 = AITRS(B[0],n,k);
        b2 = AITRS(B[1],n,k);
	if (q == 1) {
	   t = b1;
	   b1 = - b2;
	   b2 = t; }
	else if (q == 2) {
	   b1 = - b1;
	   b2 = - b2; }
	else if (q == 3) {
	   t = b1;
	   b1 = b2;
	   b2 = - t; }
	c = a1 * b1 + a2 * b2;
	if (h1 == 1) {
	   qp = q - 1;
	   if (qp < 0)
	      qp = 3;
	   t = b1;
	   b1 = b2;
	   b2 = - t; }
	else {
	   qp = q + 1;
	   if (qp > 3)
	      qp = 0;
	   t = b1;
	   b1 = - b2;
	   b2 = t; }
	cp = a1 * b1 + a2 * b2;
	if (c > cp)
	    q = qp;
	 AGIRSUM(A,B,q,C);

Return: /* Return. */
	return;
}

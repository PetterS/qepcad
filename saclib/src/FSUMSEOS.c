/*======================================================================
                        FSUMSEOS(A,B,d,C)

Floating-point sum, same exponents, opposite signs.

Inputs
   A, B : two nonzero floating-point numbers having the same precisions,
          the same exponents and opposite signs.
   d :    a sign (rounding direction).
   C :    an array large enough for the sum.

Output
   C :    a floating-point number approximating the sum of A and B,
          rounded according to IEEE standards.
======================================================================*/
#include "saclib.h"

void FSUMSEOS(A,B,d,C)
        Word *A,*B;
        BDigit d;
	Word *C;
{
	BDigit c,cp,e,h,i,j,k,n,np,p,r,s,w;

Step1: /* Compute the sign, exponent and left shift amount. */
	p = A[2];
	e = A[0];
	h = 0;
	j = p + 2;
	w = A[j] - B[j];
	if (p > 1) {
	   j = j - 1;
	   h = h + 1;
	   e = e - ZETA;
	   while (w == 0 && j >= 3) {
	      w = A[j] - B[j];
	      e = e - ZETA;
	      h = h + 1;
	      j = j - 1; }
	   j = j + 1;
	   h = h - 1;
	   e = e + ZETA; }
	if (w == 0) {
	   C[0] = 0;
	   C[1] = 0;
	   C[2] = p; 
	   goto Return; }
	if (w > 0)
	   s = 1;
	else {
	   s = -1;
	   w = - w; }
	np = 0;
        while (w < BETA2) {
           np = np + 1;
           w = w << 1; }
	n = ZETA - np;
	e = e - np;

Step2: /* Add and tentatively normalize. */
	for (k = 3; k < 3 + h; k++)
	   C[k] = 0;
	cp = 0;
	r = 0;
	if (s > 0) {
	   for (k = 3; k <= j; k++) {
	      c = A[k] - B[k] - cp;
	      if (c < 0) {
	         c = c + BETA;
	         cp = 1; }
	      else
	         cp = 0;
	      C[k + h] = ((c << np) & BETA1) | r;
	      r = c >> n; } }
	else {
	   for (k = 3; k <= j; k++) {
              c = B[k] - A[k] - cp;
              if (c < 0) {
                 c = c + BETA;
                 cp = 1; }
              else
                 cp = 0;
              C[k + h] = ((c << np) & BETA1) | r;
              r = c >> n; } }
 	
Step3: /* Renormalize if needed. */
	if (C[p + 2] >= BETA2)
	   goto Step4;
	k = p + 2;
	h = 0;
	while (C[k] == 0) {
	   e = e - ZETA;
	   h = h + 1;
	   k = k - 1; }
	w = C[k];
	np = 0;
	while (w < BETA2) {
	   np = np + 1;
	   w = w << 1;
	   e = e - 1; }
	n = ZETA - np;
	cp = (C[p + 2 - h] << np) & BETA1;
	for (i =  p + 2; i >= 3 + h; i--) {
	   r = C[i - h- 1];
	   C[i] = cp | (r >> n);
	   cp = (r << np) & BETA1; }
	C[i] = cp;
	for (i = 2 + h; i >= 3; i--)
	   C[i] = 0;
	
Step4: /* Store exponent, sign and precision. */
	C[0] = e;
	if (s > 0)
	   C[1] = A[1];
	else
	   C[1] = B[1];
	C[2] = p;

Return: /* Return. */
	return;
}

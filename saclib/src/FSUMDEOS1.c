/*======================================================================
                        FSUMDEOS1(A,B,d,C)

Floating-point sum, different exponents, opposite signs, exponent
difference of 1.

Inputs
   A, B : two nonzero floating-point numbers having the same precisions
          and opposite signs.  The exponent of A is one greater than
          the exponent of B.
   d :    a sign (rounding direction).
   C :    an array large enough for the sum.

Output
   C :    a floating-point number approximating the sum of A and B,
          rounded according to IEEE standards.

Note:  The probability that no normalizing shift is needed is 1/4.
The probability of a normalizing shift of 1 is 1/2.  The probability
of a normalizing shift of n, for n >= 2, is 3 / 4^n.
======================================================================*/
#include "saclib.h"

void FSUMDEOS1(A,B,d,C)
        Word *A,*B;
        BDigit d;
	Word *C;
{
        BDigit a,b,c,cb,cp,e,f,h,i,j,n,np,p,s,w,z;

Step1: /* Initialize the exponent, determine sign and precision. */
	e = A[0];
	s = A[1];
	p = A[2];

Step2_0: /* Try 1-pass subtraction. */
	/* Guess leading result digit. */
	cb = A[p+2] - (B[p+2] >> 1);

	/* Guess amount np of normalizing left shift. */
        w = cb;
        n = ZETA;
        while (w < BETA2) {
	  n--;
	  w = w << 1; }
        np = ZETA - n;

	/* a and f are consecutive unshifted result digits. */
	/* C contains the shifted result digits. */
	if (EVEN(B[3])) {
	  f = 0;
	  cp = 0; }
	else {
	  f = BETA2;
	  cp = -1; }
	if (np > 0)
	  C[2] = 0;
	else
	  C[2] = f;
	z = ZETA - 1;
	for (i = 3; i < p + 2; i++) {
	   a = A[i] - (((B[i+1] & 1) << z) | ((B[i] >> 1))) + cp;
	   if (a < 0) {
	     a = a + BETA;
	     cp = -1; }
	   else
	     cp = 0;
	   C[i] = ((a << np) & BETA1) | (f >> n);
	   f = a; }
	C[p+2] = (((cb + cp) << np) & BETA1) | (f >> n);

	/* Check whether result is normalized. */
	if (C[p+2] >= BETA2) {
	  e = e - np;
	  goto Step6; }

Step2: /* One-pass subtraction was unsuccessful.
	  Now perform a two-pass subtraction.
          Shift B mantissa right by 1 and subtract from A mantissa. */
	if (EVEN(B[3])) {
	  C[2] = 0;
	  cp = 0; }
	else {
	  C[2] = BETA2;
	  cp = -1; }
	z = ZETA - 1;
	for (i = 3; i < p + 2; i++) {
	   b = (B[i+1] & 1) << z;
	   c = (B[i] >> 1) | b;
	   C[i] = A[i] - c + cp;
	   if (C[i] < 0) {
	     C[i] = C[i] + BETA;
	     cp = -1; }
	   else
	     cp = 0; }
	C[p+2] = A[p+2] - (B[p+2] >> 1) + cp;

Step3: /* C mantissa already normal? */
	if (C[p+2] >= BETA2)
	   goto Step6;

Step4: /* Determine left shift amount. */
        j = p + 2;
        while (C[j] == 0)
	  j = j - 1;
        w = C[j];
        n = ZETA;
        while (w < BETA2) {
           n = n - 1;
           w = w << 1; }
        np = ZETA - n;
        h = p + 2 - j;

Step5: /* Shift left to normalize. */
        cp = C[j] << np;
        for (i = j; i > 2; i--) {
	  C[i+h] = cp | (C[i-1] >> n);
	  cp = (C[i-1] << np) & BETA1; }
        C[2 + h] = cp;
        for (i = 1 + h; i >= 2; i--)
           C[i] = 0;
	e = e - h * ZETA - np;

Step6: /* Round. */
	if (C[2] != 0 && (d==s || (d==0 && ODD(C[3])))) {
	  i = 3;
	  while (i <= p + 2 && C[i] == BETA1) {
	    C[i] = 0;
	    i = i + 1; }
	  if (i <= p + 2) 
	    C[i] = C[i] + 1;
	  else {
	    C[p+2] = BETA2;
	    e = e + 1; } }

Step7: /* Store exponent, sign, precision. */
	C[0] = e;
	C[1] = s;
        C[2] = p;

Return: /* Return. */
	return;
}

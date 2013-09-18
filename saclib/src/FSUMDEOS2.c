/*======================================================================
                        FSUMDEOS2(A,B,d,C)

Floating-point sum, different exponents, opposite signs, exponent
difference of 2 or more.

Inputs
   A, B : two nonzero floating-point numbers having the same precisions
          and opposite signs.  The exponent of A is two or more greater
          than the exponent of B.
   d :    a sign (rounding direction).
   C :    an array large enough for the sum.

Output
   C :    a floating-point number approximating the sum of A and B,
          rounded according to IEEE standards.

Note:  If d is the difference of the exponents, the probability
that a normalizing shift is required is 3 / 2^{d + 1}.
======================================================================*/
#include "saclib.h"

void FSUMDEOS2(A,B,d,C)
        Word *A,*B;
        BDigit d;
	Word *C;
{
        BDigit a,b,c,cb,e,ep,f,g,i,p,q,r,rp,s,t,z;

Step1: /* Get exponent, sign and precision. */
	e = A[0];
        s = A[1];
        p = A[2];

Step1_1: /* Initialize carry. */
	c = 0;

Step2: /* Determine input shift amount. */
	ep =  A[0] - B[0];
	if (ep < ZETA) {
	  q = 0;
	  r = ep; }
	else {
	  q = ep / ZETA;
	  r = ep - q * ZETA; }
	rp = ZETA - r;

Step2_1: /* No subtracting? */
	if (q >= p) {
	   for (i = 3; i <= p + 2; i++)
              C[i] = A[i];
           goto Step5; }

Step2_2: /* Subtract B from A. */
	if (q == 0) {
	  cb = A[p+2] - (B[p+2] >> r);
	  if (cb < BETA2) {
	    e = e - 1;
	    z = ZETA - 1;
	    f = 0;
	    for (i = 3; i <= p + 1; i++) {
	      a = A[i] - ((B[i] >> r) | ((B[i+1] << rp) & BETA1)) + c;
	      if (a < 0) {
		a = a + BETA;
		c = -1; }
	      else
		c = 0;
	      C[i] = ((a << 1) & BETA1) | f;
	      f = a >> z; }
	    a = cb + c;
	    C[p+2] = ((a << 1) & BETA1) | f;
	    goto Step4; }
	  else {
	    for (i = 3; i <= p + 1; i++) {
	      a = A[i] - ((B[i] >> r) | ((B[i+1] << rp) & BETA1)) + c;
	      if (a < 0) {
		a = a + BETA;
		c = -1; }
	      else
		c = 0;
	      C[i] = a; }
	    a = cb + c;
	    C[p+2] = a;
	    goto Step3; } }
	else {
	  for (i = q + 3; i <= p + 1; i++) {
	    a = (B[i] >> r) | ((B[i+1] << rp) & BETA1);
	    a = A[i-q] - a + c;
	    if (a < 0) {
              a = a + BETA;
              c = -1; }
	    else
              c = 0;
	    C[i-q] = a; }
	  a = A[p-q+2] - (B[p+2] >> r) + c;
	  if (a < 0) {
	    a = a + BETA;
	    c = -1; }
	  else 
	    c = 0;
	  C[p-q+2] = a; }

Step2_3: /* Propagate carry and copy. */
	for (i = p - q + 3; i <= p + 2; i++) {
	   a = A[i] + c;
	   if (a < 0) {
	      a = a + BETA;
	      c = -1; }
	   else
	      c = 0;
	   C[i] = a; }

Step3: /* Normalize. */
	if (C[p+2] >= BETA2)
           goto Step5;
	z = ZETA - 1;
        for (i = p + 2; i >= 4; i--)
           C[i] = ((C[i] << 1) & BETA1) | (C[i-1] >> z);
        C[3] = ((C[3] << 1) & BETA1);
        e = e - 1;
	
Step4: /* Subtract high-order bit of remainder from C. */
        if (r == 0) {
           r = ZETA - 1;
           q = q - 1; }
        else
           r = r - 1;
        rp = ZETA - r;
        b = (B[q+3] >> r) & 1;
        if (b == 0)
           goto Step5;
        C[3] = C[3] - 1;
        for (i = 3; C[i] < 0; i++) {
           C[i] = BETA1;
           C[i+1] = C[i+1] - 1; }

Step5: /* Compute high-order BETA-digit of remainder. */
	if (d == s)
	   goto Step8;
        if (q == 0)
           g = (B[3] << rp) & BETA1;
        else if (q < p)
           g = ((B[q+3] << rp) & BETA1) | (B[q+2] >> r);
        else if (q == p)
           g = B[p+2] >> r;
        else
           g = 0;

Step6: /* Rounding decision. */
	if (d == s)
	   goto Step8;
        if (d == -s && g != 0)
           goto Step7;
        if (d == 0) {
           if (g < BETA2)
              goto Step8;
           if (g > BETA2)
              goto Step7; }
        t = 0;
        if (q > p)
           t = 1;
        else if (q > 0 && (((B[q+2] << rp) & BETA1) != 0))
           t = 1;
        else
           for (i = q + 1; i >= 3; i--) {
              if (B[i] != 0)
                 t = 1; }
        if (d == -s) {
           if (t != 0)
              goto Step7;
           else
              goto Step8; }
	if (d == 0 ) {
           if (t != 0)
              goto Step7;
           else {
              if ((C[3] & 1) == 0)
                 goto Step8;
              else
                 goto Step7; } }

Step7: /* Round down. */
	i = 3;
	C[i] = C[i] - 1;
	while (C[i] < 0) {
	  C[i] = BETA1;
	  i++;
	  C[i] = C[i] - 1; }
	if (C[p+2] < BETA2) {
	  C[p+2] = BETA1;
	  e = e - 1; }

Step8: /* Store exponent, sign and precision. */
        C[0] = e;
        C[1] = s;
        C[2] = p;

Return: ;/* Return. */
}

/*======================================================================
                        FSUMDESS(A,B,d,C)

Floating-point sum, different exponents, same signs.

Inputs

   A, B : two floating-point numbers having the same precisions,
          different exponents, and the same signs.
   d :    a sign (rounding direction).
   C :    an array large enough for the sum.

Output
   C :    a floating-point number approximating the sum of A and B,
          rounded according to IEEE standards.
======================================================================*/
#include "saclib.h"

void FSUMDESS(A,B,d,C)
        Word *A,*B;
        BDigit d;
	Word *C;
{
	BDigit a,ap,c,cb,f,i,j,p,q,r,rp,t,u;
	Word *Ap,*Bp;

Step1: /* Let A' be the input with the larger exponent, B' the other. */
	if (A[0] >= B[0]) {
	   Ap = A;
	   Bp = B; }
	else {
	   Ap = B;
	   Bp = A; }

Step2: /* Store the exponent, sign and precision of C. */
	C[0] = Ap[0];
	C[1] = Ap[1];
	C[2] = Ap[2];
	p = Ap[2];

Step3: /* Determine the denormalizing shift amount. */
	q = 0;
	r = Ap[0] - Bp[0];
	while (r >= ZETA) {
	   q = q + 1;
	   r = r - ZETA; }
	rp = ZETA - r;

Step4: /* Add mantissas, case q = 0. */
	if (q > 0)
	   goto Step5;
	cb = Ap[p+2] + (Bp[p+2] >> r);
        if (cb >= BETA) {
	   C[0] = C[0] + 1;
	   t = 1;
           if (p == 1) {
              C[3] = cb >> 1;
              ap = cb & 1; }
           else {
              a = Ap[3] + ((Bp[3] >> r) | ((Bp[4] << rp) & BETA1));
              ap = a & 1;
              for (i = 4; i <= p+1; i++) {
                 c = a >> ZETA;
                 f = a & BETA1;
                 a = Ap[i] + ((Bp[i] >> r) | ((Bp[i+1] << rp) & BETA1)) + c;
                 C[i-1] = (f>>1) | ((a & 1) << (ZETA-1)); }
              c = a >> ZETA;
              f = a & BETA1;
              a = cb + c;
              C[p+1] = (f>>1) | ((a & 1) << (ZETA-1));
              C[p+2] = a >> 1; } }
	else { 	/* (cb < BETA) */
	   t = 0;
	   ap = 0;
	   c = 0;
	   for (i = 3; i <= p + 1; i++) {
              a = (Bp[i] >> r) | ((Bp[i+1] << rp) & BETA1);
              a = Ap[i] + a + c;
              C[i] = a & BETA1;
              c = a >> ZETA; }
           a = cb + c;
           C[p+2] = a & BETA1;
	   if (a >= BETA)
	      goto Step7; }
	goto Step8;

Step5: /* Add mantissas, case 0 < q < p. */
	if (q >= p)
	   goto Step6;
	c = 0;
	for (i = q + 3; i <= p + 1; i++) {
            a = (Bp[i] >> r) | ((Bp[i+1] << rp) & BETA1);
            a = Ap[i-q] + a + c;
            C[i-q] = a & BETA1;
            c = a >> ZETA; }
        a = (Bp[p+2] >> r) + Ap[p-q+2] + c;
        C[p-q+2] = a & BETA1;
        c = a >> ZETA;
	for (i = p - q + 3; i <= p + 2; i++) {
           a = Ap[i] + c;
           C[i] = a & BETA1;
           c = a >> ZETA; }
	if (c == 1)
	   goto Step7;
	goto Step8;

Step6: /* Add mantissas, case q >= p. */
        for (i = 3; i <= p + 2; i++)
           C[i] = Ap[i];
        t = 0;
        ap = 0;
	goto Step8;

Step7: /* Denormalizing right shift. */
	t = 1;
	ap = 1;
        for (i = p + 2; i >= 3; i--) {
           a = C[i];
           C[i] = (a >> 1) | (ap << (ZETA - 1));
           ap = a & 1; }
        C[0] = C[0] + 1;

Step8: /* Rounding decision, case d /= 0 . */

/*  Now t = 1 if a normalizing right shift occurred and otherwise
t = 0.  If t = 1 then a' is the bit that was right-shifted out of
the low-order position of the sum. */
	
	if (d == 0)
	   goto Step9;
	if (d != C[1])
	   return;
	if (q >= p)
	   goto Step12;
	if (t == 1 && ap == 1)
	   goto Step12;
	if (r != 0) {
	   u = (Bp[q+3] << rp) & BETA1;
	   j = q + 2; }
	else {
	   u = Bp[q + 2];
	   j = q + 1; }
	if (u != 0)
	   goto Step12;
	for (i = j; i >= 3; i--)
	   if (Bp[i] != 0)
	      goto Step12;
	return;

Step9: /* Rounding decision, case d = 0, t = 0 and q >= p. */
	if (t == 1)
	   goto Step11;
	if (q < p)
	   goto Step10;
	if (q > p || r > 0)
	   return;
	if (Bp[p+2] != BETA2)
	   goto Step12;
	if ((C[3] & 1) == 0)
	   return;
	goto Step12;

Step10: /* Rounding decision, case d = 0, t = 0 and q < p. */
	if (r != 0) {
           u = (Bp[q+3] << rp) & BETA1;
           j = q + 2; }
        else {
           u = Bp[q + 2];
           j = q + 1; }
	if (u < BETA2)
	   return;
	if (u > BETA2)
	   goto Step12;
	for (i = j; i >= 3; i--)
	   if (Bp[i] != 0)
	      goto Step12;
	if ((C[3] & 1) == 0)
	   return;
	goto Step12;

Step11: /* Rounding decision, case d = 0 and t = 1. */
	if (ap == 0)
	   return;
	if (r != 0) {
           u = (Bp[q+3] << rp) & BETA1;
           j = q + 2; }
        else {
           u = Bp[q + 2];
           j = q + 1; }
	if (u != 0)
	   goto Step12;
	for (i = j; i >= 3; i--)
           if (Bp[i] != 0)
              goto Step12;
        if ((C[3] & 1) == 0)
           return;

Step12: /* Round by adding 1. */
	for (i = 3; i <= p + 2; i++) {
           C[i] = C[i] + 1;
           if (C[i] != BETA)
              return;
           C[i] = 0; }
        C[p+2] = BETA2;
        C[0] = C[0] + 1;
	return;
}

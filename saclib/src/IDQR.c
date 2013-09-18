/*=================================================================
                      IDQR(A,b; Q,r)

Integer-digit quotient and remainder.

Inputs
  A  : in Z.
  b  : a non-zero BETA-digit.

Outputs
  Q  : the integral part of A / b
  r  : a BETA-digit, r = A - b * Q.
=================================================================*/
#include "saclib.h"
#define IDQR_SIZE 100

void IDQR(A,b, Q_,r_)
       Word A,b, *Q_,*r_;
{
       Word A2,*Ah,Ap[IDQR_SIZE],Q,i,k,kp,m,o,q,r,s;
       Word a0,a1,bp,q0,q1;

Step1: /* A single-precision. */
	if (A < BETA) {
           Q = A / b;
           r = A - b * Q;
           goto Return; }

Step2: /* |b| = 1. */
	r = 0;
	if (b == 1) {
	   Q = A;
	   goto Return; }
	if (b == -1) {
	   Q = INEG(A);
	   goto Return; }

Step3: /* Length of A equal to 2. */
	A2 = RED2(A);
	if (A2 == NIL) {
	   FIRST2(A,&a0,&a1);
	   DQR(0,a1,b,&q1,&r);
	   DQR(r,a0,b,&q0,&r); 
	   if (q1 == 0)
	      Q = q0;
	   else
	      Q = LIST2(q0,q1);
	   goto Return; }

Step4: /* Put dividend in array. */
	IFLTA(A,Ap,IDQR_SIZE,&Ah,&m,&s,&o);
	bp = absm(b);
	if (bp >= (01 << 15))
	   goto Step6;

Step5: /* |b| < 2^15. */
	for (i = m - 1; i >= 0; i--) {
	   PHDQR(r,Ah[i],bp,&q,&r);
	   Ah[i] = q; }
	goto Step7;

Step6: /* |b| >= 2^15. */
	k = PDLOG2(bp);
	kp = ZETA - k;
	bp = bp << kp;
	a1 = Ah[m - 1];
	r = a1 >> k;
	for (i = m - 1; i > 0; i--) {
	   a0 = ((Ah[i] << kp) & BETA1) | (Ah[i - 1] >> k);
	   PNDQR(r,a0,bp,&q,&r);
	   Ah[i] = q; }
	a0 = (Ah[0] << kp) & BETA1;
	PNDQR(r,a0,bp,&q,&r);
	Ah[0] = q;
	r = r >> kp;

Step7: /*  Adjust signs and put quotient in a list. */
	if (s < 0)
	   r = - r;
	if (b < 0)
	   s = - s;
	Q = IFATL(Ah,m,s);

Step8: /* Free dynamic array*/
	if (m > IDQR_SIZE) 
	   FREEARRAY(Ah);
  
Return: /* Prepare for return. */
	*Q_ = Q;
	*r_ = r;
	return;
}

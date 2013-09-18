/*======================================================================
                      PNDQR(a1,a0,b;q,r)

Positive normalized digit quotient and remainder.  

Inputs
   a1, a0, b : BETA-integers with a1 and a0 non-negative, b >= BETA / 2
   and a = a1 * BETA + a0 < b * BETA.

Outputs
   q : a BETA-integer, the integral part of a / b.
   r : a BETA-integer, a - b * q.

Restriction: This program is valid only if the word length is 32
   bits and ZETA = 29.
======================================================================*/
#include "saclib.h"

void PNDQR(a1,a0,b,q_,r_)
	Word a1,a0,b,*q_,*r_;
{
	Word ap1,b1,c1,c0,q,q1,q0,qp1,qp0,r;

Step1: /* a1 = 0. */
	if (a1 == 0) {
	   q = a0 / b;
	   r = a0 - b * q;
	   goto Return; }

Step2: /* Set b1 = [b / 2^14], q1 = [a1 / b1], qp1 = q1 * 2^15. */
	b1 = b >> 14;
	q1 = a1 / b1;
	qp1 = q1 << 15;

Step3: /* Subtract b * qp1 from a. */
	DPR(b,qp1,&c1,&c0);
	a0 = a0 - c0;
	if (a0 < 0) {
	   a0 = a0 + BETA;
	   a1 = a1 - 1; }
	a1 = a1 - c1;

Step4: /* Decrease q1 if the difference is negative. */
	if (a1 < 0) {
	   q1 = q1 - 1;
	   c1 = b >> 14;
	   c0 = (b << 15) & BETA1;
	   a0 = a0 + c0;
	   if (a0 >= BETA) {
	      a0 = a0 - BETA;
	      a1 = a1 + 1; }
	   a1 = a1 + c1; }

Step5: /* Set ap1 = [a / 2^15], q0 = [ap1 /b1], qp0 = q0 * 2. */
	ap1 = (a1 << 14) | (a0 >> 15);
	q0 = ap1 / b1;
	qp0 = q0 << 1;
	
	
Step6: /* Subtract b * qp0 from a. */
	DPR(b,qp0,&c1,&c0);
	a0 = a0 - c0;
	if (a0 < 0) {
           a0 = a0 + BETA;
           a1 = a1 - 1; }
        a1 = a1 - c1;

Step7: /* Decrease q0 if the difference is negative. */
	if (a1 < 0) {
	   q0 = q0 - 1;
	   c1 = 1;
	   c0 = (b << 1) & BETA1;
	   a0 = a0 + c0;
           if (a0 >= BETA) {
              a0 = a0 - BETA;
              a1 = a1 + 1; }
           a1 = a1 + c1; }

Step8: /* Set q = q1 * 2^15 + q0 * 2 and add 1 to q if necessary. */
	q = ((q1 << 14) | q0) << 1;
	if (a1 > 0) {
	   q = q + 1;
	   r = a0 - b + BETA; }
	else if (a0 >= b) {
	   q = q + 1;
	   r = a0 - b; }
	else 
	   r = a0;

Return: /* Prepare for return. */
       *q_ = q;
       *r_ = r;
       return;
}

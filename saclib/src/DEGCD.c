/*=========================================================================
                            DEGCD(a,b;c,u,v)

Digit extended greatest common divisor.

Inputs
   a, b : BETA-digits, a >= b >= 0.

Outputs
   c : a BETA-digit, c = gcd(a,b), c >= 0.
   u, v : BETA-digits such that au + bv=c,
          with |u| <= b/(2c), |v| <= a/(2c).

Method
   The Euclidean algorithm with divisions performed by shifting and
   subtraction.
===========================================================================*/
#include "saclib.h"

void DEGCD(a,b, c_,u_,v_)
       Word a,b, *c_,*u_,*v_;
{
       Word a1,a2,a3,b2,q,u,u1,u2,u3,v,v1,v2,v3,c,d;

Step1: /* b = 0. */
	if (b == 0) {
           c = a;
	   u = 0;
	   v = 0;
           goto Return; }

Step2: /* Initialize. */
	a1 = a;
	a2 = b;
	u1 = 1;
	u2 = 0;
	v1 = 0;
	v2 = 1;

Step3: /* Quotient is less than 11. */
	a3 = a1 - a2;
	u3 = u1 - u2;
	v3 = v1 - v2;
	d = a3 - a2;
	if (d < 0)
	   goto Step5;
	a3 = d;
	u3 = u3 - u2;
	v3 = v3 - v2;
	d = a3 - a2;
	if (d < 0)
	   goto Step5;
	a3 = d;
	u3 = u3 - u2;
        v3 = v3 - v2;
	d = a3 - a2;
	if (d < 0)
	   goto Step5;
	a3 = d;
	u3 = u3 - u2;
        v3 = v3 - v2;
        d = a3 - a2;
        if (d < 0)
           goto Step5;
	a3 = d;
	u3 = u3 - u2;
        v3 = v3 - v2;
        d = a3 - a2;
        if (d < 0)
           goto Step5;
	a3 = d;
	u3 = u3 - u2;
        v3 = v3 - v2;
        d = a3 - a2;
        if (d < 0)
           goto Step5;
	a3 = d;
	u3 = u3 - u2;
        v3 = v3 - v2;
        d = a3 - a2;
        if (d < 0)
           goto Step5;
	a3 = d;
        u3 = u3 - u2;
        v3 = v3 - v2;
        d = a3 - a2;
        if (d < 0)
           goto Step5;
	a3 = d;
        u3 = u3 - u2;
        v3 = v3 - v2;
        d = a3 - a2;
        if (d < 0)
           goto Step5;
	a3 = d;
        u3 = u3 - u2;
        v3 = v3 - v2;
        d = a3 - a2;
        if (d < 0)
           goto Step5;

Step4: /* Quotient is 11 or more; divide by shifting and subtraction. */
	b2 = a2 << 1;
	d = 1;
	while (b2 <= a3) {
           b2 = b2 << 1;
	   d = d << 1; }
	b2 = b2 >> 1;
	q = 0;
	while (b2 >= a2) {
	   if (b2 <= a3) {
	      a3 = a3 - b2;
	      q = q + d; }
	   d = d >> 1;
	   b2 = b2 >> 1; }
	u3 = u3 - q * u2;
	v3 = v3 - q * v2;

Step5: /* Check for completion. */
	if (a3 == 0) goto Return;

Step6: /* Update and go back to Step3. */
	a1 = a2;
	a2 = a3;
	u1 = u2;
	u2 = u3;
	v1 = v2;
	v2 = v3;
	goto Step3;

Return: /* Prepare for return. */
	*c_ = a2;
	*u_ = u2;
	*v_ = v2;
	return;
}

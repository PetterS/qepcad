/*======================================================================
                             LBRNIEEEE(A; t,F,n)

Logarithmic binary rational number to IEEE exact conversion.

Input
   A : a logarithmic binary rational number.

Outputs
   t : a BETA-digit, 0, 1 or 2.   t = 0 indicates successful
       conversion.  t = 1 indicates failure due to exponent
       limitation.  t = 2 indicates failure due to manti8ssa
       limitation.
   F : if t = 0, F is the result of the conversion.
   n : If t = 0, n is the number of trailing zero bits in the
       mantissa of F.
======================================================================*/
#include "saclib.h"

void LBRNIEEEE(A, t_,F_,n_)
	Word A;
	BDigit *t_;
	ieee *F_;
	BDigit *n_;
{
	BDigit a1,a2,ap,e,eb,h,k,kp,m0,m1,mt,n,s,t;
	Word a;
	ieee F;

Step1: /* A = 0. */
	if (A == 0) {
	   t = 0;
	   F.num = 0.0;
	   n = 52;
	   goto Return; }

Step2: /* Extract numerator and exponent of denominator. */
	FIRST2(A, &a,&h);

Step3: /* a single-precision. */
	if (a >= BETA)
	   goto Step4;
	if (a < 0) {
	   s = 1;
	   a = - a; }
	else
	   s = 0;
	k = PDLOG2(a);
	kp = ZETA - k;
	a2 = (a << kp) - BETA2;
	m1 = a2 >> 8;
	mt = a2 & 255;
	m0 = mt << 24;
	n = 53 - k;
	e = k - h;
	goto Step5;

Step4: /* a double-precision. */
	a1 = FIRST(a);
	a2 = SECOND(a);
	if (a2 < 0) {
	   a2 = - a2;
	   a1 = - a1;
	   s = 1; }
	else
	   s = 0;
	k = PDLOG2(a2);
	if (k > 24) {
	   t = 2;
	   goto Return; }
	kp = ZETA - k;
	ap = a1 >> k;
	a1 = (a1 << kp) & BETA1;
	a2 = (a2 << kp) | ap;
	m1 = (a2 - BETA2) >> 8;
	mt = a2 & 255;
	m0 = (mt << 24) | (a1 >> 5);
	n = 24 - k;
	e = ZETA + k - h;

Step5: /* Construct IEEE double. */
	eb = e + BIAS - 1;
	if (eb < 1) {
	   t = 1;
	   goto Return; }
	F.rep.sign = s;
        F.rep.exp = eb;
        F.rep.mant_h = m1;
        F.rep.mant_l = m0;
	t = 0;

Return: /* Return t, F and n. */
	*t_ = t;
        *F_ = F;
	*n_ = n;
        return;
}

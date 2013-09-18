/*======================================================================
                             LBRNIEEE(A,d; F,u)

Logarithmic binary rational number to IEEE conversion.

Inputs
   A : a logarithmic binary rational number.
   d : rounding direction:
       d = -1 : round down.
       d =  0 : round to nearest.
       d =  1 : round up.

Outputs
   F : a hardware float.
       If d = -1, F is the greatest hardware float that is <= A;
       If d = 1, F is the smallest hardware float that is >= A.
       If d = 0, F is the hardware float that is nearest to A, and
       is even if two are equally near.
   u : If u = 0, exponent overflow or underflow occurred and F is 
       undefined.  Otherwise u = 1.
======================================================================*/
#include "saclib.h"

void LBRNIEEE(A,d,F_,u_)

	Word A;
        BDigit d;
	ieee *F_;
	BDigit *u_;
{
        BDigit e,k,u;
        Word a;
        ieee F;

Step1: /* A = 0. */
	if (A == 0) {
	   F.num = 0.0;
	   u = 1;
	   goto Return; }

Step2: /* Extract mantissa, exponent. */
	FIRST2(A,&a,&k);

Step3: /* Convert mantissa, increment exponent. */
	IIEEE(a,d, &F,&u);
	if (u == 0)
	   goto Return;
	else {
	   e = F.rep.exp;
	   e = e - k;
	   if (e <= 0) {
	      u = 0;
	      goto Return; }
	   F.rep.exp = e;
	   u = 1; }

Return: /* Return F and u. */
	*F_ = F;
	*u_ = u;
        return;
}

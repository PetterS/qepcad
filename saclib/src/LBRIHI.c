/*========================================================================
			LBRIHI(I; J,t)

Logarithmic binary rational interval to hardware interval.

Input
   I : a logarithmic binary rational interval.

Outputs
   J : the smallest hardware interval containing I.
   t : If t = 0, the program failed and J is undefined.  Otherwise t = 1.
=========================================================================*/
#include "saclib.h"

void LBRIHI(I,J_,t_)
	Word I;
	interval *J_;
	BDigit *t_;
{
	Word a,b;
	ieee ap,bp;
	interval J;
	BDigit t;

Step1: /* Convert endpoints and make interval. */
	FIRST2(I,&a,&b);
	LBRNIEEE(a,-1,&ap,&t);
	if (t == 0)
	   goto Return;
	LBRNIEEE(b,+1,&bp,&t);
	if (t == 0)
	   goto Return;
	J.left = ap.num;
	J.right = bp.num;

Return: /* Return J and t. */
	*J_ = J;
	*t_ = t;
	return;
}

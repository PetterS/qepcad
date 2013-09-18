/*======================================================================
                           HIPVCHT(n,A; v,t)

Hardware interval polynomial, variations after circle to half-plane 
transformation.

Inputs
    n : a BETA-digit, n >= 1.
    A : in HI[X], deg(A) = n.

Outputs
    v :  A beta-digit.  Let B(x) = x^n A(1/x), C(x) = B(x + 1).
         If t = 0, v is an indication of the number of sign 
         variations in C(x) as follows.  If v = 0 or 1, v is the
         number of variations.  If v = 2, the number of
         variations is at least 2.  If t /= 0 then v is undefined.
    t :  0,1 or 2.  If t = 1, the program failed due to
	 exponent limitation.  If t = 2, the program failed due 
	 to mantissa limitation.
======================================================================*/
#include "saclib.h"

void HIPVCHT(n,A, v_,t_)
	BDigit n;
	interval *A;
	BDigit *v_,*t_;
{
	interval a,*B,*C;
	BDigit t,v;
	double b;

Step1: /* Compute B(x). */
	FPCATCH();
	B = HIPRT(n,A);

Step2: /* Compute C(x). */
	FPCATCH();
	C = HIPTR1(n,B);
	FREEARRAY(B);
	if (FPCHECK() == 1) {
	   FPCATCH();
	   FREEARRAY(C);
	   t = 1;
	   goto Return; }

Step3: /* Count variations. */
	v = HIPSV(n,C);
	FREEARRAY(C);
	if (v < 0)
	   t = 2;
	else
	   t = 0;

Return: /* Return v and t. */
	*v_ = v;
	*t_ = t;
	return;
}

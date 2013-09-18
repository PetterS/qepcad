/*======================================================================
                        HIPBHT(n,A,k; B,t)

Hardware interval polynomial binary homothetic transformation.

Inputs
   n : a BETA-digit.
   A : in HI[X], deg(A) = n.
   k : a BETA-digit.
  
Outputs
   B : in HI[x]. If t = 1, B(x) = A(2^k * x); otherwise B is undefined.
   t : t = 1 if no exponent overflow occurs; otherwise t = 0.
======================================================================*/
#include "saclib.h"

void HIPBHT(n,A,k,B_,t_)
	BDigit n;
	interval A[];
	BDigit k;
	interval **B_;
	BDigit *t_;
{
	interval *B;
	BDigit e,i,t;
	ieee F;
	double f,g;

Step1: /* k = 0. */
	if (k == 0) {
	   B = HIPCOPY(n,A);
	   t = 1;
	   goto Return; }

Step2: /* Get array. */
	B = GETHIPARRAY(n);

Step3: /* Construct floating-point numbers 1 and  2^k. */
	F.rep.sign = 0;
	F.rep.exp = k + BIAS;
	F.rep.mant_h = 1 << 20;
	F.rep.mant_l = 0;
	f = F.num;
	g = 1.0;

Step4: /* Compute the homothetic transform. */
	FPCATCH();
	for (i = 0; i <= n; i++) {
	   B[i].left = A[i].left * g;
	   B[i].right = A[i].right * g;
	   g = g * f; }
	if (FPCHECK() == 1) {
	   t = 0;
	   FPCATCH(); }
	else
	   t = 1;

Return: /* Return B and t. */
	*B_ = B;
	*t_ = t;
	return;
}

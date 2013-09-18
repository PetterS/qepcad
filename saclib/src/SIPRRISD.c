/*======================================================================
                      L <- SIPRRISD(A,a,b)

Software interval polynomial real root isolation, standard interval,
Descartes' method.

Inputs
   A :  a software interval polynomial of positive degree.  A[n] 
        does not contain 0.
   a,b: logarithmic binary rational numbers such that (a,b) is an
        open logarithmic standard interval.

Output
   L :  either 0 or a list (I_1,...,I_r), r >= 0, of standard and 
        one-point binary rational intervals, with I_1 < ... < I_r.
	Let T(x) = (b - a) x + a, the linear transformation that
	maps the interval (0,1) onto the interval (b - a).  Let
	A*(x) = U(A(x)), where U is the inverse of T.  If L /= 0,
	L is a list of isolating intervals for the roots of A*(x)
	in (a,b).  If L = 0, the program was not able to produce
	such a list using software interval arithmetic of 
        precision p, where p is the precision of A.
======================================================================*/
#include "saclib.h"

Word SIPRRISD(A,a,b)
	BDigit *A;
	Word a,b;
{
	BDigit *B,*C,s,S,t,v;
	Word c,L,L1,L2;

Step1: /* Case that A has at most one variation, */
	v = SIPVCHT(A);
	if (v == 0) {
	   L = NIL;
	   goto Return; }
	if (v == 1) {
	   L = LIST1(LIST2(a,b));
	   goto Return; }
	if (v == NIL) {
	   L = 0;
	   goto Return; }

Step2: /* Copy A into an array B. */
	S = SIPSIZE(A);
	B = GETARRAY(S);
        SIPCOPY(A,B);

Step3: /* Isolate roots of A in (0,1/2). */
	SIPBHT(B,-1);
	c = LBRIMID(LIST2(a,b));
	t = LBRNSIGN(c);
	if (t > 0)
	   L1 = SIPRRISD(B,a,c);
	else
	   L1 = SIPRRISD(B,c,b);
	if (L1 == 0 ) {
	   FREEARRAY(B);
	   L = 0;
	   goto Return; }

Step4: /* Isolate roots of A in (1/2,1). */
	C = GETARRAY(SIPSIZE(B));
	SIPTR1(B,C);
	FREEARRAY(B);
	s = SISIGN(C + 1);
	if (t > 0)
	   L2 = SIPRRISD(C,c,b);
	else
	   L2 = SIPRRISD(C,a,c);
	if (L2 == 0) {
	   L = 0;
	   goto Step6; }

Step5: /* Include midpoint if a root. */
	if (t > 0) {
	   if (s == 0)
	      L2 = COMP(LIST2(c,c),L2);
	   L = CONC(L1,L2); }
	else {
	   if (s == 0) 
	       L1 = COMP(LIST2(c,c),L1);
           L = CONC(L2,L1); }

Step6: /* Free array C. */
	FREEARRAY(C);

Return: /* Return L. */
	return(L);
}

/*======================================================================
                   L <- modSIPRRISD(A,a,b)

Software interval polynomial real root isolation, standard interval,
Descartes' method, modified so that "don't know" intervals may be
returned.

Inputs
   A :  a software interval polynomial of positive degree.  A[n] 
        does not contain 0.
   a,b: logarithmic binary rational numbers such that (a,b) is an
        open logarithmic standard interval.

Output
   L :  a list (I_1,...,I_r), r >= 0, of the form I_i = (a_i,b_i,e_i), 
        where e_i is either 1 or zero, and (a_i,b_i) is a standard or
        one-point binary rational interval, with I_1 < ... < I_r.
	Let T(x) = (b - a) x + a, the linear transformation that
	maps the interval (0,1) onto the interval (b - a).  Let
	A*(x) = U(A(x)), where U is the inverse of T.  If L /= 0,
	L is a list of isolating intervals for the roots of A*(x)
	in (a,b).  If e_i is 0, then (a_i,b_i) is known to be an isolating
	interval for a root of A.  If e_i is 1, then the program
	could not determine the number of roots (if any) in the
	interval (a_i,b_i)
======================================================================*/
#include "lift2d.h"

Word modSIPRRISD(BDigit *A, Word a, Word b)
{
	BDigit *B,*C,s,S,t,v;
	Word c,L,L1,L2;

Step1: /* Case that A has at most one variation, */
	v = SIPVCHT(A);
	if (v == 0) {
	   L = NIL;
	   goto Return; }
	if (v == 1) {
	   L = LIST1(LIST3(a,b,0));
	   goto Return; }
	if (v == NIL) {
	  L = LIST1(LIST3(a,b,1));
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
	   L1 = modSIPRRISD(B,a,c);
	else
	   L1 = modSIPRRISD(B,c,b);


Step4: /* Isolate roots of A in (1/2,1). */
	C = GETARRAY(SIPSIZE(B));
	SIPTR1(B,C);
	FREEARRAY(B);
	s = SISIGN(C + 1);

	/* Sign at the midpoint cannot be determined! */
	if (s == NIL) {
	  L = LIST1(LIST3(a,b,1));
	  FREEARRAY(C);
	  goto Return; }

	if (t > 0)
	   L2 = modSIPRRISD(C,c,b);
	else
	   L2 = modSIPRRISD(C,a,c);

Step5: /* Include midpoint if a root. */
	if (t > 0) {
	   if (s == 0)
	     L2 = COMP(LIST3(c,c,0),L2);
	   L = CONC(L1,L2); }
	else {
	   if (s == 0) 
	       L1 = COMP(LIST3(c,c,0),L1);
           L = CONC(L2,L1); }

Step6: /* Free array C. */
	FREEARRAY(C);

Return: /* Return L. */
	return(L);
}

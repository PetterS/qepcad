/*======================================================================
                      HIPRRISD(n,A,a,b; L,t)

Hardware interval polynomial real root isolation, standard interval,
Descartes' method.

Inputs
   n :  a positive beta-digit.
   A :  a hardware interval polynomial of degree n.  A[n] 
        does not contain 0.
   a,b: logarithmic binary rational numbers, a < b such that
        (a,b) is a standard interval.

Outputs
   L : Let T be the linear transformation that maps the interval
       (a,b) onto the interval (0,1).  If t = 0, L is a list of
       standard and one-point binary rational isolating
       intervals for the roots of A(T(x)) in (a,b).  If L = 
       (I_1,I_2,...,I_r) then I_1 < I_2 < ... < I_r and each I_j
       is a subinterval of (a,b).  If t /= 0 then L is undefined.
   t : 0, 1 or 2.  If t = 1, the program failed to produce the
       list L because of exponent limitation.  If t = 2, the
       failure is due to mantissa limitation.
======================================================================*/
#include "saclib.h"

void HIPRRISD(n,A,a,b, L_,t_)
	BDigit n;
	interval *A;
	Word a,b,*L_;
	BDigit *t_;
{
	BDigit s,s2,t,u,v;
	Word c,L,L1,L2;
	interval *B,*C;

Step1: /* Case that A has at most one variation, */
	HIPVCHT(n,A, &v,&t);
	if (t != 0)
	   goto Return;
	if (v == 0) {
	   L = NIL;
	   goto Return; }
	if (v == 1) {
	   L = LIST1(LIST2(a,b));
	   goto Return; }

Step2: /* Isolate the roots of A in (0,1/2). */
	HIPBHT(n,A,-1, &B,&t);
	if (t == 0) {
	   FREEARRAY(B);
	   t = 1;
	   goto Return; }
	c = LBRIMID(LIST2(a,b));
	s = LBRNSIGN(c);
	if (s > 0)
	   HIPRRISD(n,B,a,c, &L1,&t);
	else
	   HIPRRISD(n,B,c,b, &L1,&t);
	if (t >0) {
	   FREEARRAY(B);
	   goto Return; }

Step3: /* Isolate the roots of A in (1/2,1). */
	FPCATCH();
	C = HIPTR1(n,B);
	FREEARRAY(B);
	if (FPCHECK()) {
	   FREEARRAY(C);
	   t = 1;
	   goto Return; }
	s2 = HISIGN(C[0]);
	if (s2 == NIL) {
	   FREEARRAY(C);
	   t = 2;
	   goto Return; }
	if (s > 0)
	   HIPRRISD(n,C,c,b, &L2,&t);
	else
	   HIPRRISD(n,C,a,c, &L2,&t);
	FREEARRAY(C);
	if (t > 0)
	   goto Return;

Step4: /* Include midpoint if a root. */
	if (s > 0) {
	   if (s2 == 0)
	      L2 = COMP(LIST2(c,c),L2);
	   L = CONC(L1,L2); }
	else {
	   if (s2 == 0) 
	       L1 = COMP(LIST2(c,c),L1);
           L = CONC(L2,L1); }

Return: /* Return L and t. */
	*L_ = L;
	*t_ = t;
	return;
}

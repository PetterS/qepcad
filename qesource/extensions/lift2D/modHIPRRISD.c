/*======================================================================
                      L <-- modHIPRRISD(n,A,a,b)

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
======================================================================*/
#include "lift2d.h"

Word modHIPRRISD(BDigit n, interval *A, Word a, Word b)
{
	BDigit s,s2,t,u,v,Th,T0,sh;
	Word c,L,L1,L2;
	interval *B,*C,J;

Step1: /* Case that A has at most one variation, */
	T0 = 0; Th = 0;
	HIPVCHT(n,A, &v,&t);
	if (t != 0) {
	  T0 = 1;
	  goto Step4; }
	if (v == 0) {
	  L =  NIL;
	  goto Return; }
	if (v == 1) {
	  L = LIST1(LIST3(a,b,0));
	  goto Return; }

Step2: /* Isolate the roots of A in (0,1/2). */
	HIPBHT(n,A,-1, &B,&t);
	if (t == 0) {
	   FREEARRAY(B);
	   T0 = 1;
	   goto Step4; }
	c = LBRIMID(LIST2(a,b));

	LBRIHI(LIST2(LIST2(1,1),LIST2(1,1)),&J,&t);
	sh = HISIGN(HIPIEVAL(n,A,J));
	if (sh == NIL) {
	  T0 = 1;
	  FREEARRAY(B);
	  goto Step4; }
	if (sh == 0) {
	  Th = 1; }

	s = LBRNSIGN(c);
	if (s > 0)
	  L1 = modHIPRRISD(n,B,a,c);
	else
	  L1 = modHIPRRISD(n,B,c,b);


Step3: /* Isolate the roots of A in (1/2,1). */
	FPCATCH();
	C = HIPTR1(n,B);
	FREEARRAY(B);
	if (FPCHECK()) {
	  if (s > 0)
	    L2 = LIST1(LIST3(c,b,1));
	  else
	    L2 = LIST1(LIST3(a,c,1));
	   FREEARRAY(C);
	   goto Step4; }
	s2 = HISIGN(C[0]);
	if (s2 == NIL) {
	  if (s > 0)
	    L2 = LIST1(LIST3(c,b,1));
	  else
	    L2 = LIST1(LIST3(a,c,1));
	   FREEARRAY(C);
	   goto Step4; }
	if (s > 0)
	  L2 = modHIPRRISD(n,C,c,b);
	else
	  L2 = modHIPRRISD(n,C,a,c);
	FREEARRAY(C);

Step4: /* Isolate the roots of A in (1/2,1). */
	if (T0 == 1)
	  L = LIST1(LIST3(a,b,1));
	else
	  if (Th == 0)
	    if (s > 0)
	      L = CONC(L1,L2);
	    else
	      L = CONC(L2,L1);
	  else
	    if (s > 0)
	      L = CONC(L1,COMP(LIST3(c,c,0),L2));
	    else
	      L = CONC(L2,COMP(LIST3(c,c,0),L1));

Return: /* Return L. */	    
	return L;
}

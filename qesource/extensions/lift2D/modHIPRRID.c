/*======================================================================
                      modHIPRRID(n,A; L,t)

Hardware interval polynomial real root isolation, Descartes method.

Inputs
   n : a positive beta-digit.
   A : a hardware interval polynomial of degree n.  A(x) contains
       a squarefree polynomial and A[n] does not contain 0.

Outputs
   L : If t = 0, L is a a list (I_1,...,I_r), r >= 0, of standard
       and one-point binary rational intervals, with I_1 < ... , I_r,
       that isolates the real roots of A.  If t /= 0, L is
       undefined.
   t : 0, 1 or 2.  If t = 1, isolation failed due to exponent
       limitation.  If t = 2, failure was due to mantissa limitation.
======================================================================*/
#include "lift2d.h"

void modHIPRRID(BDigit n, interval *A, Word *L_, BDigit *t_)
{
	BDigit k,s,t;
	interval *B,*C;
	Word b,I,J,L,L1,L2;

Step1: /* Compute a bound for the positive roots. */
	k = HIPPRB(n,A);

Step2: /* Isolate the positive roots. */
	if (k == NIL) {
	   L1 = NIL;
	   goto Step3; }
	HIPBHT(n,A,k, &B,&t);
	if (t == 0) {
	   FREEARRAY(B);
	   t = 1;
	   goto Return; }
	L1 = modHIPRRISD(n,B,0,LIST2(1,-k));
	FREEARRAY(B);

Step3: /* Compute a bound for the negative roots. */
	B = HIPNEGT(n,A);
	k = HIPPRB(n,B);

Step4: /* Isolate the negative roots. */
	if (k == NIL) {
           L2 = NIL;
           goto Step5; }
        HIPBHT(n,B,k, &C,&t);
	FREEARRAY(B);
	if (t == 0) {
	   FREEARRAY(C);
	   t = 1;
	   goto Return; }
        L2 = modHIPRRISD(n,C,LIST2(-1,-k),0);
	FREEARRAY(C);

Step5: /* Include 0 if a root. */
	s = HISIGN(A[0]);
	if (s == NIL) {
	  t = 2; /* This is a problem!!!! */
	   goto Return; }
	if (s == 0) {
	   I = LIST3(0,0,0);
	   L1 = COMP(I,L1); }

Step6: /* Concatenaate L_2 and L_1. */
	L = CONC(L2,L1);
	t = 0;

Return: /* Return L and t. */
	*L_ = L;
	*t_ = t;
	return;
}

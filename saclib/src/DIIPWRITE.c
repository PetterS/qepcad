/*===========================================================================
			      DIIPWRITE(r,A,V)

Distributive integral polynomial write. 

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Z[x_1,...,x_r], distributive representation.
      A is written in the output stream. 
  V : a variable list for A.
===========================================================================*/
#include "saclib.h"

void DIIPWRITE(r,A,V)
       Word r,A,V;
{
       Word Ap,E,Eb,Ep,Vb,Vp,a,e,s,v;
       char fc,z;

Step1: /* r = 0 or A = 0. */
       if (r == 0 || A == 0) {
	  IWRITE(A);
	  goto Return; }

Step2: /* Initialize */
       Ap = A;
       fc = 1;
       CWRITE('(');

Step3: /* General case. */
       do {
	  ADV2(Ap,&a,&E,&Ap);
	  /* write coefficient */
	  s = ISIGNF(a);
	  if (fc == 1) {
	     fc = 0;
	     if (a != 1 && a != -1) {
		CWRITE(' ');
		IWRITE(a); }
	     else
		if (a == -1) 
		   SWRITE(" -"); }
	  else {
	     CWRITE(' ');
	     if (a != 1 && a != -1) {
		if (s > 0)
		   CWRITE('+');
		IWRITE(a); }
	     else 
		if (a == 1)
		   CWRITE('+');
		else 
		   CWRITE('-'); }
	  /* write monomial */
	  Ep = CINV(E);
	  Vp = V;
	  z = 0;
	  do {
	     ADV(Ep,&e,&Ep);
	     ADV(Vp,&v,&Vp);
	     if (e > 0) {
		z = 1;
		CWRITE(' ');
		CLOUT(v); }
	     if (e > 1) {
		CWRITE('^');
		AWRITE(e); } }
	  while (Ep != NIL);
	  if (z == 0 && (a == 1 || a == -1))
	     CWRITE('1'); }
       while (Ap != NIL);
       SWRITE(" )");

Return: /* Prepare for return. */
       return;
}

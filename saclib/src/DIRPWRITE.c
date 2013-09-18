/*===========================================================================
			      DIRPWRITE(r,A,V)

Distributive rational polynomial write. 

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Q[X1,...,Xr], distributive representation.
      A is written in the output stream. 
  V : a variable list for A.
===========================================================================*/
#include "saclib.h"

void DIRPWRITE(r,A,V)
       Word r,A,V;
{
       Word Ap,E,Eb,Ep,Vb,Vp,a,e,s,v,p1,n1;
       char fc,z;

Step1: /* r = 0 or A = 0. */
       if (r == 0 || A == 0) {
	  RNWRITE(A);
	  goto Return; }

Step2: /* Initialize */
       Ap = A;
       p1 = RNINT(1);
       n1 = RNINT(-1);
       fc = 1;
       CWRITE('(');

Step3: /* General case. */
       do {
	  ADV2(Ap,&a,&E,&Ap);
	  /* write coefficient */
	  s = RNSIGN(a);
	  if (fc == 1) {
	     fc = 0;
	     if (!(EQUAL(a,p1) || EQUAL(a,n1))) {
		CWRITE(' ');
		RNWRITE(a); }
	     else
		if (EQUAL(a,n1)) 
		   SWRITE(" -"); }
	  else {
	     CWRITE(' ');
	     if (!(EQUAL(a,p1) || EQUAL(a,n1))) {
		if (s > 0)
		   CWRITE('+');
		RNWRITE(a); }
	     else 
		if (EQUAL(a,p1))
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
	  if (z == 0 && (EQUAL(a,p1) || EQUAL(a,n1)))
	     CWRITE('1'); }
       while (Ap != NIL);
       SWRITE(" )");
       
Return: /* Prepare for return. */
       return;
}

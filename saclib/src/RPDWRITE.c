/*===========================================================================
			      RPDWRITE(r,A,V)

Rational Polynomial Distributive Write.

Inputs
  r : a non-negative BETA--integer.
  A : an element of Q[x_1,...,x_r], 
  V : a list of at least r distinct variables.
      First r variables in V are used.

Side effects
  A is written out to the output stream.
======================================================================*/
#include "saclib.h"

void RPDWRITE(r,A,V)
       Word r,A,V;
{
       Word Ap,E,Ep,Vp,a,e,l,s,t,v;

Step1: /* r = 0 or A = 0. */
       Ap = DIPFP(r,A);
       if (r == 0 || Ap == 0) {
	  RNWRITE(Ap);
	  goto Return; }
       l = 1;

Step2: /* General case. */
       do {
	  ADV2(Ap,&a,&E,&Ap);
	  s = RNSIGN(a);
	  a = RNABS(a);
	  if (s > 0 && l == 0)
	     CWRITE('+');
	  if (s < 0)
	     CWRITE('-');
	  if (!EQUAL(a,RNRED(1,1))) {
	     if (l == 0)
		CWRITE(' ');
	     RNWRITE(a); t = 1; }
	  else
             t = 0;
	  Ep = CINV(E);
	  Vp = V;
	  do {
	     ADV(Ep,&e,&Ep);
	     ADV(Vp,&v,&Vp);
	     if (e > 0) {
		if (l == 0 || t == 1)
		   CWRITE(' ');
		VWRITE(v);
		t = 1; }
	     if (e > 1) {
		CWRITE('^');
		AWRITE(e); } }
	  while (Ep != NIL);
	  if (t == 0) {
	     if (l == 0)
		CWRITE(' ');
	     CWRITE('1'); }
	  if (Ap == NIL)
	     goto Return;
	  CWRITE(' ');
	  l = 0; } 
       while (1);

Return: /* Prepare for return. */
       return;
}

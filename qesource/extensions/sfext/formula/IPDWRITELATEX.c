/*===========================================================================
			      IPDWRITELATEX(r,A,V)

Integral polynomial distributive write.

Input
  r : a non-negative BETA-integer.
  A : in Z[x_1,...,x_r].
  V : a list of at least r distinct variables.

Side effects
  A is written out to the output stream using the first r variables in V.
===========================================================================*/
#include "qepcad.h"

void IPDWRITELATEX(Word r, Word A, Word V)
{
       Word Ap,E,Ep,Vp,a,e,l,s,t,v;

Step1: /* r=0 or A=0. */
       Ap = DIPFP(r,A);
       if (r == 0 || Ap == 0) { 
          IWRITE(Ap);
          goto Return; }
       l = 1;

Step2: /* General case. */
        do {
	   ADV2(Ap,&a,&E,&Ap);
	   s = ISIGNF(a); 
	   a = IABSF(a);
	   if (s > 0 && l == 0) 
	      CWRITE('+');
	   if (s < 0) 
	      CWRITE('-');
	   if (a != 1) {
	      if (l == 0) 
		 CWRITE(' '); 
	      IWRITE(a); 
	      t = 1; }
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
		 CWRITE('{'); 
		 AWRITE(e); } 
		 CWRITE('}'); }
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

/*=======================================================================
				a <- PFFGEN(p)

Prime finite field generator.

Inputs
   p : a prime beta digit.

Output
   a : the least primitive element of Z_p.
========================================================================*/
#include "saclib.h"

BDigit PFFGEN(p)
	BDigit p;
{
	BDigit a,b,d,e,pp;
	Word L,Lp,M;

Step1: /* p = 2 */
        if (p == 2) {
           a = 1;
	   goto Return; }

Step2: /* Let p' = p - 1.  Make a list L of all p'/d such that d is
          a prime divisor of p'. */
	pp = p - 1;
	L = IFACT(pp);
	M = LFML(L);
	L = NIL;
	do {
	   ADV(M,&d,&M);
	   L = COMP(pp/d,L); }
	while (M != NIL);

Step3: /* Search for a primitive element. */
	for (a = 2; a < p; a++) {
	   Lp = L;
	   do {
	      ADV(Lp,&e,&Lp);
	      b = MDEXP(p,a,e); }
	   while (Lp != NIL && b != 1);
	   if (Lp == NIL && b != 1)
	      goto Return; }

Return: /* Return a. */
	return(a);
}

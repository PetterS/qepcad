/*=====================================================================
		  L <- IPRRISS(M,a,b,v1,v2,s)

Integral polynomial real root isolation, standard interval,
Sturm method.

Inputs  
   M:      a list (A_1,A_2,...,A_t) of integral univariate
           polynomials.  M is a Sturm sequence for A_1.
   a, b:   logarithmic binary rational numbers, a < b.
           (a,b) is an open standard interval.
   v1, v2: integers.  v1 = var(M,a).  v2 = var(M,b)
   s:      sign(A_1(b)).

Outputs
   L : a list (I_1,...,I_r) of standard isolating intervals for
       the real roots of A1 in the interval (a,b), I_1 < I_2 
       < ... < I_r.  Each I_j is a one-point or open binary
       rational interval.
=====================================================================*/
#include "saclib.h"

Word IPRRISS(M,a,b,v1,v2,s)
       Word M,a,b,v1,v2,s;
{
       Word L,L1,c,S,t,v,w2;

Step1: /* No roots or only 1 in (a,b). */
       if (s == 0)
	  w2 = v2 - 1;
       else 
	  w2 = v2;
       if (v1 - w2 == 0) {
	  L = NIL;
	  goto Return; }
       if (v1 - w2 == 1) {
	  L = LIST1(LIST2(a,b));
	  goto Return; }

Step2: /* Count variations at the midpoint, c. */
       c = LSIM(a,b);
       S = IPLSEVAL(M,c);
       v = VAR(S);

Step3: /* Isolate roots in (c,b). */
       L = IPRRISS(M,c,b,v,v2,s);

Step4: /* Is c a root? */
       t = FIRST(S);
       if (t == 0)
	  L = COMP(LIST2(c,c),L);

Step5: /* Isolate roots in (a,c). */
       L1 = IPRRISS(M,a,c,v1,v,t);

Step6: /* Concatenate lists. */
       L = CONC(L1,L);

Return: /* Return L. */
       return(L);
}

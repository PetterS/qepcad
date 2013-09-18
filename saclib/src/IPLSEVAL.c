/*======================================================================
		       S <- IPLSEVAL(L,a)

Integral polynomial list sign evaluation, logarithmic.

Inputs  
   L : a list (A_1,A_2,...,A_t) of univariate integral polynomials.
   a : a logarithmic binary rational number.

Outputs
   L : the list (s_1,...,s_t) where s_i = sign(A_i(a)).
======================================================================*/
#include "saclib.h"

Word IPLSEVAL(L,a)
       Word L,a;
{
       Word s;
       Word A,Lp,S;

Step1: /* Initialize. */
       Lp = L;
       S = NIL;

Step2: /* Evaluate polynomials. */
       while (Lp != NIL) {
	  ADV(Lp,&A,&Lp);
	  s = IUPBRES(A,a);
	  S = COMP(s,S); }
       S = INV(S);

Return: /* Return S. */
       return(S);
}

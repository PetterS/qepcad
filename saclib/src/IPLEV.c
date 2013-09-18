/*===========================================================================
			      L <- IPLEV(S,a)

Integral polynomial list evaluation of signs.
 
Inputs  
  S : a list (A_1,A_2,...,A_t) of univariate integral polynomials.
  a : a binary rational number.

Outputs
  L : a list (s_1,...,s_t).  s_i = sign(A_i(a)).
===========================================================================*/
#include "saclib.h"

Word IPLEV(S,a)
       Word S,a;
{
       Word L,A,Sp,s;

Step1: /* Initialize. */
       Sp = S;
       L = NIL;

Step2: /* Evaluate polynomials. */
       while (Sp != NIL) {
	  ADV(Sp,&A,&Sp);
	  s = IUPBES(A,a);
	  L = COMP(s,L); }
       L = INV(L);

Return: /* Prepare for return. */
       return(L);
}

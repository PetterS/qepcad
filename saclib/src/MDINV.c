/*===========================================================================
			      b <- MDINV(m,a)

Modular digit inverse.  

Inputs
  m : a positive BETA-digit, m > 1.
  a : a unit of Z_m, a BETA-digit.

Output
  b : a^{-1}, the inverse of a in Z_m, a BETA-digit.
===========================================================================*/
#include "saclib.h"

Word MDINV(m,a)
       Word m,a;
{
       Word a1,a2,a3,b,q,v1,v2,v3;

Step1: /* Compute. */
       a1 = m;
       a2 = a;
       v1 = 0;
       v2 = 1;
       while (a2 != 1) {
	  q = a1 / a2;
	  a3 = a1 - q * a2;
	  v3 = v1 - q * v2;
	  a1 = a2;
	  a2 = a3;
	  v1 = v2;
	  v2 = v3; }
       if (v2 >= 0)
	  b = v2;
       else
	  b = v2 + m;

Return: /* Prepare for return. */
       return(b);
}

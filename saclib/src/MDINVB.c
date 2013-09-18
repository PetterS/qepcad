/*===========================================================================
			       b <- MDINVB(a)

Modular digit inverse, modulo BETA.

Inputs:
  a : an odd positive BETA-integer.

Output
  b : a^{-1}, the inverse of a modulo BETA, a positive BETA-integer.

Method:  Jebelean's method is applied four times.

Warning: This program is correct only if BETA = 2^29;
         otherwise it must be modified.
===========================================================================*/
#include "saclib.h"

Word MDINVB(a)
       Word a;
{
       Word a1,a2,b,b1,b2,c,d,i;

Step1: /* Look up the inverse modulo 2^8 in the global array TMI. */
       a1 = a & 0377;
       i = a1 >> 1;
       b1 = TMI[i];

Step2: /* Compute the inverse modulo 2^15. */
       a2 = a & 077777;
       c = a2 * b1 - 1;
       c = c & 077777;
       if (c != 0)
	  c = 0100000- c;
       c = c * b1 + b1;
       b2 = c & 077777;

Step3: /* Compute the inverse modulo 2^29. */
       DPR(a,b2,&d,&c);
       c = c - 1;
       if (c != 0)
	  c = BETA - c;
       DPR(c,b2,&d,&c);
       c = c + b2;
       b = c & BETA1;

Return: /* Return. */
       return(b);
}

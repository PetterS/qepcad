/*======================================================================
                             IEEEWRITE(F)

IEEE write.

Input
   F : a hardware float.

Effect
   The sign, high-order mantissa, low-order mantissa, and exponent
   are written as the elements of a list.  The low-order mantissa 
   is broken into a 5-bit unsigned integer followed by a 27-bit
   unsigned integer.
======================================================================*/
#include "saclib.h"

void IEEEWRITE(F)
        ieee F;
{
        unsigned m1,m0;
        int s,e;
        BDigit a,b;
        Word L;
        ieee_rep G;

Step1: /* Decompose F. */
       G = F.rep;
       s = G.sign;
       m1 = G.mant_h;
       m0 = G.mant_l;
       e = G.exp - BIAS;

Step2: /* Break up the high-order mantissa. */
	a = m0 >> 27;
	b = (m0 << 5) >> 5;

Step3: /* Compoise and write list. */
	L = LIST5(s,m1,a,b,e);
	LWRITE(L);

Return: /* Return. */
	return;
}

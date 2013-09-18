/*======================================================================
                      LBRNDWRITE(R,n)

Logarithmic binary rational number decimal write. 

Inputs
   R : a logaritghmic binary rational number.
   n : a non-negative integer.  

Effect
   R is printed as a rounded decimal fraction with n decimal digits
   following the decimal point, and with a trailing '+' or '-' 
   indicating whether the exact value is larger or smaller.
======================================================================*/
#include "saclib.h"

void LBRNDWRITE(R,n)
        Word R;
	BDigit n;
{
        Word S;

Step1: /* Convert from logarithmic representation. */
	S = LBRNRN(R);

Step2: /* Apply RNDWRITE. */
        RNDWRITE(S,n);

Return: /* Return. */
         return;
}

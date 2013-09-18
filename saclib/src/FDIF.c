/*======================================================================
                        FDIF(A,B,d,C)

Floating-point difference.

Inputs
 
   A, B : floating-point numbers of the same precision.
   d : a sign (rounding direction).
   C : an array large enough for the difference.

Output
   C :    a floating-point number approximating A - B, rounded
          according to IEEE standards.
======================================================================*/
#include "saclib.h"

void FDIF(A,B,d,C)
	Word *A,*B;
        BDigit d;
	Word *C;
{

Step1: /* Change the sign of B and add. */
	B[1] = - B[1];
	FSUM(A,B,d,C);
	B[1] = - B[1];

Return: /* Return. */
	return; 
}

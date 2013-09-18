/*======================================================================
                           J <- HIPIEVAL(n,A,I)

Hardware interval polynomial interval evaluation.

Inputs
   n : a BETA-digit.
   A : a hardware interval polynomial of degree n.
   I : a hardware interval.

Output
   J :  a hardware interval containing A(I).

Warning
   HIPIEVAL is not floating-point overflow-underflow protected.
======================================================================*/
#include "saclib.h"

interval HIPIEVAL(n,A,I)
       BDigit n;
       interval A[],I;
{
	BDigit i;
	interval J;
	Word L;

Step1: /* Apply Horner's method. */
	J = A[n];
	for (i = n - 1; i >= 0; i--) {
	   J = HIPROD(J,I);
	   J = HISUM(J,A[i]); }

Return: /* Return J. */
	return(J);
}

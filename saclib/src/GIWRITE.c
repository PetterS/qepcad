/*=======================================================================
                              GIWRITE(a)

Gaussian integer write.

Input
   a : a Gaussian integer.

Effect
   a is written to the output stream in the form a1 + a2 i.
=======================================================================*/
#include "saclib.h"

void GIWRITE(a)
	Word a;
{
	Word b;
	BDigit s;

Step1: /* Write the output. */
	if (a == 0)
	   IWRITE(0);
	else {
	   b = SECOND(a);
	   if (FIRST(a) != 0) {
	      IWRITE(FIRST(a));
	      if (b != 0) {
	         s = ISIGNF(b);
	         if (s > 0)
	            SWRITE (" + ");
	         else {
	            b = INEG(b);
	            SWRITE(" - "); }
	         if (b != 1)
	            IWRITE(b);
	         SWRITE(" i"); } }
	   else {
	      if (b == 1)
	         SWRITE("i");
	      else if (b == -1)
	         SWRITE("- i");
	      else {
	         IWRITE(b);
	         SWRITE(" i"); } } }

Return: /* Return. */
	return;
}

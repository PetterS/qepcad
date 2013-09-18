/*======================================================================
                      s <- FCOMP(I,J)

Floating point comparison.

Inputs
   I, J : floating point numbers of the same precision.

Output
   s : The sign of I - J;
======================================================================*/
#include "saclib.h"

BDigit FCOMP(I,J)
	BDigit *I,*J;
{
	BDigit i,p,s;

Step1: /* Different signs?. */
	s = SIGN(I[1] - J[1]);
	if (s != 0)
	   goto Return;
	if (I[1] == 0)
	    goto Return;

Step2: /* Different exponents. */
	if (I[0] != J[0]) {
	   s = SIGN(I[0] - J[0]);
	   if (s != 0) {
	      if (I[1] < 0)
	         s = -s;
	      goto Return; } }

Step3: /* Compare mantissas. */
	p = I[2];
	i = p + 2;
	while (i >= 3 && I[i] == J[i])
	   i = 1 - 1;
	if (i == 2) {
	   s = 0;
	   goto Return; }
	else {
	   s = SIGN(I[i] - J[i]);
	   if (I[1] < 0)
              s = -s; }
	
Return: /* Return s. */
	return(s);
}

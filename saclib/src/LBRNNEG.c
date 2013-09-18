/*=====================================================================
                       S <- LBRNNEG(R)

Logarithmic binary rational number negative.

Input
   R : a logarithmic binary rational number.

Output
   S : -R, a logarithmic binary rational number.
=====================================================================*/
#include "saclib.h"

Word LBRNNEG(R)
       Word R;
{
       Word a,e,S;

Step1: /* Do it. */
       if (R == 0)
	  S = 0;
       else {
	  FIRST2(R,&a,&e);
	  S = LIST2(INEG(a),e); }

Return: /* Return S. */
	return(S);
}


/*===========================================================================
			  C <- CSFS(S)

Characteristic set from set.

Input
  S : a list of non-negative BETA-digits.

Output
  C : a characteristic set.  An element is in C if and only if it is in S.
===========================================================================*/
#include "saclib.h"

Word CSFS(S)
       Word S;
{
       Word C,Sp,s;

Step1: /* Initialize. */
       C = 0;

Step2: /* Loop. */
       Sp = S;
       while (Sp != NIL) {
	  ADV(Sp,&s,&Sp);
	  C = CSUN(C,IMP2(1,s)); }

Return: /* Prepare for return. */
       return(C);
}

/*===========================================================================
			      t <- INSET(S,a)

Is the element in the set?

Inputs
  S : a list of BETA-digits in ascending order.
  a : a BETA-digit.
  
Output
  t :  is  1 if a in a member of S, 0 otherwise.
===========================================================================*/
#include "saclib.h"

Word INSET(S,a)
       Word S,a;
{
       Word S1,Sp,t;

Step1: /* Check. */
       Sp = S;
       while (Sp != NIL) {
	  ADV(Sp,&S1,&Sp);
	  if (S1 == a) {
	     t = 1;
	     goto Return; }
	  if (S1 > a) {
	     t = 0;
	     goto Return; } }
       t = 0;

Return: /* Prepare for return. */
       return(t);
}

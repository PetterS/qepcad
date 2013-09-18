/*===========================================================================
                              d <- PGCDE(r,A,i)

Polynomial greatest common divisor of exponents.

Inputs
   r : a positive beta digit.
   A : a nonzero polynomial in r variables over any domain.
   i : a beta digit, 1 <= i <= r.

Output
   d : the greatest common divisor of all exponents of x^i in A.
======================================================================*/
#include "saclib.h"

Word PGCDE(r,A,i)
	BDigit i,r;
	Word A;
{
	BDigit d,e;
	Word a,Ap;

Step1: /* i = r. */
	if (i == r) {
	   Ap = A;
	   d = 0;
	   while (Ap != NIL) {
	      ADV2(Ap,&e,&a,&Ap);
	      if (e > d)
	         d = DGCD(e,d);
	      else
	         d = DGCD(d,e);
	      if (d == 1)
	         goto Return; }
	   goto Return; }

Step2: /* i < r. */
	Ap = A;
	d = 0;
	while (Ap!= NIL) {
	   ADV2(Ap,&e,&a,&Ap);
	   e = PGCDE(r-1,a,i);
	   if (e > d)
	      d = DGCD(e,d);
	   else
	      d = DGCD(d,e);
	   if (d == 1)
	      goto Return; }
	
Return: /* Return d. */
	return(d);
}

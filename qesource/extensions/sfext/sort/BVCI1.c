/*======================================================================
                      b <- BVCI1(u,v,n)

BETA-digit vector comparison indexed from 1.

Inputs
u : An array of n BETA-digits.
v : An array of n BETA-digits.
n : A positive BETA-digit.
Output
b : -1 if u < v in lex order, 0 if u = v, 1 if u > v.
  ======================================================================*/
#include "qepcad.h"

Word BVCI1(Word *u_, Word *v_, Word n)
{
       Word *w,*u,*v;
       u = u_+1;
       v = v_+1;
       w = u + n;
       while (u < w) {
	 if (*u < *v)
	   return (-1);
	 if (*u > *v)
	   return (1);
	 u++;
	 v++; }

       return (0);
}

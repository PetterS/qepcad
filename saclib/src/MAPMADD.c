/*===========================================================================
		       MAPMADD(m,A,b,j,C)

Modular array polynomial multiply and add.

Input
  m : a BETA-digit.
  A : in Z/(m)[x] in array representation.
  b : in Z/(m).
  j : an exponent such that j + deg(A) <= deg(C). 
  C : in Z/(m)[x] in array representation.

Side effect
  C is modified such that C <- C + A(x) * b * x^j.
===========================================================================*/
#include "saclib.h"

void MAPMADD(m,A,b,j,C)
       Word m,*A,b,j,*C;
{
       Word n,i,a,c,k;

Step1: /* A = 0 or b = 0. */
       if (MAPZERO(A) || b == 0)
	  goto Return;

Step2: /* Otherwise. */  
       n = MAPDEG(A);
       for (i = 0; i <= n; i++) {  
	  a = MAPCF(A,i);
	  k = i + j;
	  if (a != 0) {
	     c = MDSUM(m,MDPROD(m,a,b),MAPCF(C,k));
	     MAPCF(C,k) = c; } }
       
Return: /* Prepare for return. */
       return;
}

/*===========================================================================
		      MMAPMADD(m,A,b,j,C)

Medium modulus array polynomial multiply and add.

Input
  m : a medium BETA-digit.
  A : in Z/(m) in array representation.
  b : in Z/(m).
  j : a non-negative BETA-digit such that j + deg(A) <= deg(C).
  C : in Z/(m) in array representation.

Side effect
  C is modified such that C <- C + A(x) * b * x^j.
===========================================================================*/
#include "saclib.h"

void MMAPMADD(m,A,b,j,C)
       Word m,*A,b,j,*C;
{
       Word n,i,a,k,c;

Step1: /* b = 0 or A = 0. */
       if (b == 0 || MAPZERO(A))
	  goto Return;

Step2: /* Otherwise. */  
       n = MAPDEG(A);
       for (i = 0; i <= n; i++) {  
	  a = MAPCF(A,i);
	  k = i + j;
	  if (a != 0) { 
	     c = (a * b + MAPCF(C,k)) % m;
	     MAPCF(C,k) = c; } }

Return: /* Prepare for return. */
       return;
}

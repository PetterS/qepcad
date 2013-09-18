/*===========================================================================
		      e <- MMAPEVAL(m,A,s)

Medium modulus array polynomial evaluation.

Inputs
  m : a medium BETA-digit.
  A : in Z/(m), deg(A) > 0, A is in array representation.
  s : an element of Z/(m).

Output
  e : an element of Z/(m), e = A(s).
===========================================================================*/
#include "saclib.h"

Word MMAPEVAL(m,A,s)
       Word m,*A,s;
{
       Word n,e,i;

Step1: /* Apply Horner's rule. */
       n = MAPDEG(A);
       e = MAPLDCF(A);
       for (i = n-1; i >= 0; i--) 
	  e = (e * s + MAPCF(A,i)) % m;

Return: /* Prepare for return. */
       return(e);
}

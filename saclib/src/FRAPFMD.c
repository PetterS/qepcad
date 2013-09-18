/*==========================================================================
		       A <- FRAPFMD(c,n)

Finite ring array polynomial from modular digit.

Inputs
  c : in Z/(m), for some positive BETA-digit m.
  n : a BETA-digit, n >= 2.

Outputs
  A : in (Z/(m)[x])/(M)[y].  A = c in array representation.  deg(M) = n.
==========================================================================*/
#include "saclib.h"

Word **FRAPFMD(c,n)
       Word c,n;
{
       Word **A,*a;
       
Step1: /* Construct A. */
       A = FRAPGET(0,n);
       FRAPDEG(A) = 0;
       a = FRAPCF(A,0);
       MAPDEG(a) = 0;
       MAPCF(a,0) = c;
       
Return: /* Prepare for return. */
       return(A);
}

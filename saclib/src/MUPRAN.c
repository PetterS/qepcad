/*======================================================================
                      A <- MUPRAN(p,n)

Modular univariate polynomial, random.

Inputs
  p : a BETA-digit.
  n : a BETA-digit.

Outputs
  A : in Z/(p)[X], a random polynomial of degree n.
======================================================================*/
#include "saclib.h"

Word MUPRAN(p,n)
       Word p,n;
{
       Word A,a,i;
       /* hide a,i; */

Step1: /* Compute. */
       A = NIL;
       for (i = 0; i <= n - 1; i++)
         {
         a = MDRAN(p);
         if (a != 0)
           A = COMP2(i,a,A);
         }
       a = MDRAN(p - 1) + 1;
       A = COMP2(n,a,A);

Return: /* Prepare for return. */
       return(A);
}

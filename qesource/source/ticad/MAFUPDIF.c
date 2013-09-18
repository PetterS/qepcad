/*==========================================================================
                    C <- MAFUPDIF(p,A,B)

Modular algebraic field univariate polynomial difference.

Input
  p : a BETA-digit, p a prime.
  A,B : in (Z/(p)[x])/(M)[y], M in Z/(p)[x].

Output
  C : in (Z/(p)[x])/(M)[y], C = A - B.
==========================================================================*/
#include "qepcad.h"

Word MAFUPDIF(Word p, Word A, Word B)
{
       Word C;

Step1: /* Compute. */
       C = MPDIF(2,p,A,B);

Return: /* Prepare for return. */
       return(C);
}

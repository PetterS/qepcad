/*==========================================================================
                    b <- MAFHOM(p,M,a)

Modular algebraic field homomorphism.

Inputs
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x].
  a : in Z/(p)[x].

Output
  b : the image of a in Z/(p)[x]/(M).
==========================================================================*/
#include "qepcad.h"

Word MAFHOM(Word p, Word M, Word a)
{
       return(MUPNR(p,a,M));
}

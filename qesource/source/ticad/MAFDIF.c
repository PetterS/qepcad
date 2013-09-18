/*==========================================================================
                    c <- MAFDIF(p,a,b);

Modular algebraic field element difference.

Input
  p : a BETA-digit, p a prime.
  a,b : in Z/(p)[x]/(M),  M in Z/(p)[x].

Output
  c : in Z/(p)[x]/(M), c = a - b.
==========================================================================*/
#include "qepcad.h"

Word MAFDIF(Word p, Word a, Word b)
{
       return(MPDIF(1,p,a,b));
}

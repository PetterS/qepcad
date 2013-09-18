/*==========================================================================
                      c <- MAFPROD(p,M,a,b);

Modular algebraic field element product.

Input
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x].
  a,b : in Z/(p)[x]/(M).


Output
  c : in Z/(p)[x]/(M), c = a * b.
==========================================================================*/
#include "qepcad.h"

Word MAFPROD(Word p, Word M, Word a, Word b)
{
       Word c;
  
Step1: /* a = 0 \/ b = 0 */
       if (a == 0 || b == 0) {
	 c = 0;
	 goto Return;
       }

Step2: /* Compute product. */
       c = MPPROD(1,p,a,b);

Step3: /* Compute residue modulo M. */
       c = MAFHOM(p,M,c);

Return: /* Prepare for return. */
       return(c);
}

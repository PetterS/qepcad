/*===========================================================================
			     M <- COMP2(a,b,L)

Composition 2.

Inputs
  a, b  : objects.
  L     : list.

Outputs
  M     : the list (a,b) concatenated with the list L.
===========================================================================*/
#include "saclib.h"

Word COMP2(a,b,L)
       Word a,b,L;
{
       Word M,N;

Step1: /* Store a. */
       M = AVAIL;
       if (M == NIL) {
	  GC();
	  goto Step1; }
       SFIRST(M,a);

Step2: /* Store b. */
       N = RED(M);
       if (N == NIL) {
	  GC();
	  goto Step1; }
       SFIRST(N,b);

Step3: /* Set AVAIL to the reductum of N. */
       AVAIL = RED(N);

Step4: /* Set the reductum of N to L. */
       SRED(N,L);

Return: /* Prepare for return. */
       return(M);
}

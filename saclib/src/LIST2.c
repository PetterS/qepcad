/*======================================================================
                      L <- LIST2(a,b)

List, 2 elements.

Inputs
  a,b : objects.

Outputs
  L  : the list (a,b).
======================================================================*/
#include "saclib.h"

Word LIST2(a,b)
	Word a,b;
{
	Word L,M;

Step1: /* Store a. */
        L = AVAIL;
        if (L == NIL) {
           GC();
           goto Step1; }
        SFIRST(L,a);

Step2: /* Store b. */
        M = RED(L);
        if (M == NIL) {
           GC();
           goto Step1; }
        SFIRST(M,b);

Step3: /* Set AVAIL to reductum of M. */
	AVAIL = RED(M);

Step4: /* Set reductum of M to NIL. */
        SRED(M,NIL);

Return: /* Prepare for return. */
       return(L);
}

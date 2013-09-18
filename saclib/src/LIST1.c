/*======================================================================
                      L <- LIST1(a)

List, 1 element.

Inputs
  a  : an object.

Outputs
  L  : the list (a).
======================================================================*/
#include "saclib.h"

Word LIST1(a)
	Word a;
{
	Word L;

Step1: /* Store a. */
	L = AVAIL;
	if (L == NIL) {
           GC();
           goto Step1; }
        SFIRST(L,a);

Step2: /* Set AVAIL to reductum of L. */
	AVAIL = RED(L);

Step3: /* Set reductum of L to NIL. */
	SRED(L,NIL);

Return: /* Prepare for return. */
       return(L);
}

/* Polynomial from label. */
/* o is a label and P is a proj fac/pol data structure. */
#include "qepcad.h"

Word POLFLAB(Word o, Word P)
{
      Word r,P_r,p;

Step1: /* Initialize. */
      r = SECOND(o);
      P_r = LELTI(P,r);

Step2: /* Search P_r for a pol with label o. */
      while ( P_r != NIL && ! EQUAL(o,LELTI(FIRST(P_r),PO_LABEL)) ) {
	P_r = RED(P_r); }

Step3: /* Set return value p to the pol if it's found, and 0 otherwise. */
      if ( P_r != NIL )
	p = FIRST(P_r);
      else
	p = 0;

Return: /* Return. */
      return (p);
}

/*======================================================================
                     S <- PFSUNION(S1,S2)

Projection factor set union.

inputs
  S1: A set of qepcad projection factor data structures.
  S2: A set of qepcad projection factor data structures.
outputs
  S : The union of S1 and S2;
======================================================================*/
#include "qepcad.h"

Word PFSUNION(Word S1, Word S2)
{
      Word S,R,s;

Step1: /* Initialize. */
      S = S1;

Step2: /* Set R to the list of labels of pol's in S1. */
      for(R = NIL; S1 != NIL; S1 = RED(S1))
	R = COMP(LELTI(FIRST(S1),PO_LABEL),R);

Step3: /* For each pol in S2, if its lable is not in R, add pol to S. */
      for(; S2 != NIL; S2 = RED(S2)) {
	s = FIRST(S2);
	if ( ! MEMBER(LELTI(s,PO_LABEL),R) )
	  S = COMP(s,S); }

Return: /* Prepare to return. */
      return (S);

}

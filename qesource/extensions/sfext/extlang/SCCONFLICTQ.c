/*======================================================================
                    t <- SCCONFLICTQ(L1,L2)

SC Conflict query.

Inputs
L1,L2: Lists of ESCAD cells.

Outputs
t: 1 if there are cells in L1 and L2 with the same signitures,
   0 otherwise.

======================================================================*/
#include "extlang.h"

Word SCCONFLICTQ(Word L1, Word L2)
{
  Word t,Q1,Q2,q1,q2,S1,S2,S1p;

Step1: /* Set t. */
  for(t = 0, Q1 = L1; Q1 != NIL && !t; Q1 = RED(Q1)) {
    q1 = FIRST(Q1);
    S1p = LELTI(q1,SC_SIGN);
    for(Q2 = L2; Q2 != NIL && !t; Q2 = RED(Q2)) {
      q2 = FIRST(Q2);
      S2 = LELTI(q2,SC_SIGN);
      for(t = 1, S1 = S1p; S1 != NIL && t; S1 = RED(S1), S2 = RED(S2))
	t = (FIRST(S1) == FIRST(S2)); } }

Return: /* Prepare to return. */
  return t;

}

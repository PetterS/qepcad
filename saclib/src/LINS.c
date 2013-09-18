/*======================================================================
                      LINS(a,L)

List insertion.

Inputs
  L  : a non-null list ( a1,...,an )
  a  : object

Side effects:
  L is modified by inserting a after the first element in L,
  so L will become (a1,a,a2,...,an).
======================================================================*/
#include "saclib.h"

void LINS(a,L)
       Word a,L;
{
       Word A;
       /* hide algorithm */

Step1: /* Compute. */
       A = COMP(a,RED(L));
       SRED(L,A);

Return: /* Prepare for return. */
       return;
}

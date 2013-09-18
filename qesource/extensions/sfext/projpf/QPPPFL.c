/*======================================================================
                      d <- QPPPFL(P,L)

Query: Polynomial in pruned projection factor list?

Inputs
  P  : a qepcad polynomial data structure.
  L  : a pruned projection factor list.

Outputs
  d  : 1 if P in L, 0 otherwise.
======================================================================*/
#include "qepcad.h"

Word QPPPFL(Word P, Word L)
{
      Word d,P_l,P_i,l,q,q_l;

Step1: /* Initialize. */
      d = 0;
      P_l = LELTI(P,PO_LABEL);
      P_i = LELTI(P_l,2);
      if (P_i > LENGTH(L)) {
	d = 0; goto Return; }
      l = LELTI(L,P_i);

Step2: /* Search for polynomial in l with label P_l. */
      while( (l != NIL) && (d == 0) ) {
	ADV(l,&q,&l);
	q_l = LELTI(q,PO_LABEL);
	d = EQUAL(P_l,q_l); }

Return: /* Prepare to return. */
      return (d);

}


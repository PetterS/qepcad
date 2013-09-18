/*======================================================================
                      cp <- HAC_CONS(c,P)

Half adjacency Cell construct.

Inputs
  c : a QEPCAD cell structure
  P : the projection factor set.

Outputs
  cp: an Adj2D_Cell structure representing c.
Note: c need not be a 2D cell for this to create the appropriate
      Adj2D_Cell structure.  
======================================================================*/
#include "newadj2D.h"

Word HAC_CONS(Word c, Word P)
{
  Word r,P_r,n,i,M,L,k,m,T,p,cp,I;

Step1: /* Construct empty multiplicity vector. */
  r = LELTI(c,LEVEL);
  P_r = LELTI(P,r);
  n = LENGTH(P_r);
  for(i = 0, M = NIL; i < n; i++)
    M = COMP(0,M);

Step2: /* Set non-zero entries from cells multiplicity list. */
  for(L = LELTI(c,MULSUB); L != NIL; L = RED(L)) {
    FIRST2(FIRST(L),&k,&m);

    /*-- Find p, the p.f. with index k. --*/
    for(T = P_r, i = 1; T != NIL; T = RED(T),i++) {
      p = FIRST(T);
      if (k == THIRD(LELTI(p,PO_LABEL)))
	break; }

    /*-- Proj.fac. with index k has been removed from the set. --*/
    if (T == NIL) continue;

    SLELTI(M,i,m); }

Return: /* Construct cp and return. */
  I = LELTI(c,INDX);
  cp = LIST2(I,M); 
  return cp;
}


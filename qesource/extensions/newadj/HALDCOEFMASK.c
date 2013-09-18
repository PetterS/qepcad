/*======================================================================
                      v <- HALDCOEFMASK(c,P,J)

Half Assignment Leading coefficient mask.

Inputs
  D  : a CAD
  c  : a zero-dimensional cell
  P  : the projection factor set.
  J  : the projection polynomial set.

Outputs
  v  : a characteristic vector for the set of projection factors of level
       1 greater than c with a leading coefficient that vanishes in c.

Note: A PO_LABEL conisist of 3 fields, the second is the level and
      the third is the index amongst pols of that level.
======================================================================*/
#include "newadj2D.h"

Word HALDCOEFMASK(Word D, Word c, Word P, Word J)
{
  Word n,i,v,L,P_k,q,h,lc,F,f,k,Lp;

Step1: /* Construct empty characteristic vector. */
  k = LELTI(c,LEVEL) + 1;
  n = LENGTH(LELTI(P,k));
  v = ZERO_VECTOR(n);

Step2: /* Set L to the set of p.f.'s which are zero in c. */
  L = LPFZCAL(D,c,P);

Step3: /* Loop over each level k projection factor and determine
          if its leading coefficient vanishes in c. */

  for(P_k = LELTI(P,k), i = 1; P_k != NIL; P_k = RED(P_k), i++) {
    
  /*-- q is the ith k-level projection factor. ------------------*/
    q = FIRST(P_k);

  /*-- Set lc to the projection polynomial which is ldcoef of q.-*/
    h = LIST3(PO_LCO,0,q);
    lc = PPWITHHIST(J,k-1,h);
    if (lc) {

  /*-- Set F to the list of proj fac's which are factors of lc. -*/
      F = LIST_OF_FACS(lc,P);
  
  /*-- If F intersect L non-empty then some factor of lc vanishes
    -- in c, so set ith element of v to 1. ----------------------*/
      for(;F != NIL; F = RED(F)) {
	f = FIRST(F);
	for(Lp = L; Lp != NIL && f != FIRST(Lp); Lp = RED(Lp));
	if (Lp != NIL) {
	  SLELTI(v,i,1);
	  break; } } } }

Return: /* Prepare to return. */
  return v;  
}

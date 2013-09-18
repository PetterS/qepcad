/*======================================================================
                      v <- LDCOEFMASK(c,P,J)

Leading coefficient mask.

Inputs
  c  : a section cell in the 1D CAD.
  P  : the projection factor set.
  J  : the projection polynomial set.

Outputs
  v  : a characteristic vector for the set of level 2 projection
       factors with a leading coefficient which vanishes in c.

Note: A PO_LABEL conisist of 3 fields, the second is the level and
      the third is the index amongst pols of that level.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"
#define nEw
#ifdef nEw

Word LDCOEFMASK(Word c, Word P, Word J)
{
  Word *A,P_2,n,i,M,P_1,L,m,j,p,Lp,h,q,v,l;

Step1: /* Set up A to be a characteristic vector for the set of
level 2 proj fac's whose leading coefficients vanish in c. */
  P_2 = LELTI(P,2);
  n = THIRD(LELTI(LAST(P_2),PO_LABEL));
  A = GETARRAY(n + 1);
  for(i = 1; i <= n; i++)
    A[i] = 0;

Step2: /* Set L to be the list of projection factors which vanish in c. */
  M = LELTI(c,MULSUB);
  P_1 = LELTI(P,1);
  L = NIL;
  while(M != NIL) {
    ADV(M,&m,&M);
    j = FIRST(m); 
    do
      ADV(P_1,&p,&P_1);
    while(j != THIRD(LELTI(p,PO_LABEL)));
    L = COMP(p,L); }

Step3: /* Set Lp to the list of projection polynomials with factors in L. */
  Lp = NIL;
  while(L != NIL) {
    ADV(L,&p,&L);
    for(h = LELTI(p,PO_PARENT); h != NIL; h = RED(h))
      Lp = COMP(THIRD(FIRST(h)),Lp); }

Step4: /* Run through the histories of each polynomial in Lp.  If the 
polynomial is the leading coefficient of some bivariate projection factor,
set A at the index for that projection factor to 1. */
  while(Lp != NIL) {
    ADV(Lp,&p,&Lp);
    for(h = LELTI(p,PO_PARENT); h != NIL; h = RED(h)) {
      q = FIRST(h);
      if (FIRST(q) == PO_LCO) {
	l = LELTI(THIRD(q),PO_LABEL);
	if (SECOND(l) == 2)
	  A[ THIRD(l) ] = 1; } } }

Step5: /* Create the vector itself! */
  v = NIL;
  while(P_2 != NIL) {
    ADV(P_2,&p,&P_2);
    j = THIRD(LELTI(p,PO_LABEL));
    v = COMP(A[j],v); }
  v = INV(v);

Return: /* Prepare to return. */
  FREEARRAY(A);
  return v;
}

#else
Word LDCOEFMASK(c,P,J)
       Word c,P,J;
{
  Word n,i,v,L,P_2,q,h,lc,F;

Step1: /* Construct empty characteristic vector. */
  n = LENGTH(LELTI(P,2));
  v = ZERO_VECTOR(n);

Step2: /* Set L to the set of p.f.'s which are zero in c. */
  L = LPFZC(c,P);

Step3: /* Loop over each level 2 projection factor and determine
	  if its leading coefficient vanishes in c. */

  for(P_2 = LELTI(P,2), i = 1; P_2 != NIL; P_2 = RED(P_2), i++) {
    
  /*-- q is the ith level 2 projection factor. ------------------*/
    q = FIRST(P_2);

  /*-- Set lc to the projection polynomial which is ldcoef of q.-*/
    h = LIST3(PO_LCO,0,q);
    lc = PPWITHHIST(J,1,h);
    if (lc) {

  /*-- Set F to the list of proj fac's which are factors of lc. -*/
      F = LIST_OF_FACS(lc,P);
  
  /*-- If F intersect L non-empty then some factor of lc vanishes
    -- in c, so set ith element of v to 1. ----------------------*/
      if (LPFSETINTERSECT(F,L) != NIL)
	SLELTI(v,i,1); } }

Return: /* */
  return v;  
}
#endif

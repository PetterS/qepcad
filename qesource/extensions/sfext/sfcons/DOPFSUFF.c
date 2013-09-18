/*======================================================================
                     t <- DOPFSUFF(P,D)

Do the projection factors suffice?

inputs
 P  : Projection factor set data structure.
 K  : A list of partial CAD cells, all in a CAD defined by P, and
      all with the same signiture.
outputs
 t  : NIL if no solution formula exists using the pols in P.
      Otherwise, TRUE, FALSE, UNDET or NA.
      TRUE (FALSE)  if all cells in substrees rooted at cells K which 
      have truth values have truth value TRUE (FALSE).  Otherwise
      UNDET.
======================================================================*/
#include "qepcad.h"

static Word comp(Word A, Word B);
#define BDCOMP(a,b)       ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
	  
Word DOPFSUFF(Word P, Word K)
{
      Word t,L,Kp,Lp,T,F,N,Lpp,tp;

Step1: /* Initialize. */
      if (LELTI(FIRST(K),LEVEL) == 0 && LELTI(FIRST(K),CHILD) == NIL) {
	t = LELTI(FIRST(K),TRUTH);
	goto Return; }
      else
	t = NIL;

Step3: /* List cells of level r, sorted by signiture. */
      L = NIL;
      for(Kp = K; Kp != NIL; Kp = RED(Kp)) {
	L = CCONC(LELTI(FIRST(Kp),CHILD),L); }
      L = GMSL(L,comp);

Step4: /* Loop over each block of cells with same signiture. */
      while (L != NIL) {
	Lp = NIL;
	do {
	  Lp = COMP(FIRST(L),Lp);
	  L = RED(L);
	} while (L != NIL && comp(FIRST(Lp),FIRST(L)) == 0);

Step5: /* Get the number of TRUE leaf cells and FALSE leaf cells. */
	T = 0; F = 0; N = 0;
	for(Lpp = Lp; Lpp != NIL; Lpp = RED(Lpp)) {
	  switch( LELTI(FIRST(Lpp),TRUTH) ) {
	  case TRUE : T++; break;
	  case FALSE: F++; break;
	  case NA:    N++; break; } }

Step6: /* Case:  All cells are leaf cells. */
	if (T + F + N == LENGTH(Lp)) {
	  if ( T == 0 && F == 0 ) { tp = NA; goto Step8; }
	  if ( T > 0 && F == 0 )  { tp = TRUE; goto Step8; }
	  if ( F > 0 && T == 0 )  { tp = FALSE; goto Step8; }
	  t = NIL; goto Return; }

Step7: /* Case:  Not all cells are leaf cells. */
	tp = DOPFSUFF(P,Lp);
	if ( ( F == 0 && T == 0 && tp != NIL) ||
	     ( F == 0 && T > 0 && tp == TRUE ) ||
	     ( F > 0 && T == 0 && tp == FALSE ) )
	  goto Step8;
	t = NIL; goto Return;

Step8: /* Set t to the proper value.  t = NIL at this step only if
	  it is the first time through the loop. */
	if (t == NIL || t == NA) 
	  t = tp;
	else if (tp != NA && t != tp)
	  t = UNDET; }

Return: /* Prepare to return. */
      return (t);
}

	
/*-- Comparison of signitures of cells.  Both cells 
  -- are assumed to be of the same level, and both cells are
  -- assumed to have the same signiture on all projection factors
  -- of level lower than the cells themselves. */

static Word comp(Word A, Word B)
{
      Word S_a,S_b,s_a,s_b,t;

Step1: /* Initialization. */
      S_a = LELTI(A,SIGNPF);
      S_b = LELTI(B,SIGNPF);
      t = 0;

Step2: /* Compare siginitures. */
	ADV(S_a,&s_a,&S_a); ADV(S_b,&s_b,&S_b);
	while ( t == 0 && s_a != NIL) {
	  t = BDCOMP(FIRST(s_a),FIRST(s_b)); 
	  s_a = RED(s_a); s_b = RED(s_b); }

Return: /* Return. */
      return (t);
}

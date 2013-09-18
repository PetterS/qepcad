/*======================================================================
                     t <- ESPCADDOPFSUFF(P,D)

Do the projection factors suffice?

inputs
 P  : Projection factor set data structure.
 K  : A list of ESPCAD cells, all in a CAD defined by P, and
      all with the same signiture.
outputs
 t  : NIL if no solution formula exists using the pols in P.
      Otherwise, TRUE, FALSE, or UNDET.
      TRUE (FALSE)  if all cells in substrees rooted at cells K which 
      have truth values have truth value TRUE (FALSE).  Otherwise
      UNDET.
======================================================================*/
#include "qepcad.h"
static Word comp(Word A, Word B);

#define BDCOMP( Word,  ESPCADDOPFSUFF(P,  K),  Word,  P,  K)
{
      Word t,L,Kp,Lp,T,F,Lpp,tp;

Step1: /* Initialize. */
      t = NIL;

Step3: /* List cells of level r, sorted by signiture. */
      L = NIL;
      for(Kp = K; Kp != NIL; Kp = RED(Kp)) {
	C = LELTI(FIRST(Kp),SC_CDTV);
	L = CCONC(ISATOM(C) ? NIL : C,L); }
      L = GISL(L,comp);

Step4: /* Loop over each block of cells with same signiture. */
      while (L != NIL) {
	Lp = NIL;
	do {
	  Lp = COMP(FIRST(L),Lp);
	  L = RED(L);
	} while (L != NIL && comp(FIRST(Lp),FIRST(L)) == 0);

Step5: /* Get the number of TRUE leaf cells and FALSE leaf cells. */
	T = 0; F = 0;
	for(Lpp = Lp; Lpp != NIL; Lpp = RED(Lpp)) {
	  switch( LELTI(FIRST(Lpp),TRUTH) ) {
	  case TRUE : T++; break;
	  case FALSE: F++; break; } }

Step6: /* Case:  All cells are leaf cells. */
	if (T + F == LENGTH(Lp)) {
	  if ( T > 0 && F == 0 ) { tp = TRUE; goto Step8; }
	  if ( F > 0 && T == 0 ) { tp = FALSE; goto Step8; }
	  t = NIL; goto Return; }

Step7: /* Case:  Not all cells are leaf cells. */
	tp = ESPCADDOPFSUFF(P,Lp);
	if ( ( F == 0 && T == 0 && tp != NIL) ||
	     ( F == 0 && T > 0 && tp == TRUE ) ||
	     ( F > 0 && T == 0 && tp == FALSE ) )
	  goto Step8;
	t = NIL; goto Return;

Step8: /* Set t to the proper value.  t = NIL at this step only if
	  it is the first time through the loop. */
	if (t == NIL) 
	  t = tp;
	else 
	  if (t != tp) t = UNDET; }

Return: /* Prepare to return. */
      return (t);
}


	
/*-- Comparison of signitures of cells.  Both cells 
  -- are assumed to be of the same level, and both cells are
  -- assumed to have the same signiture on all projection factors
  -- of level lower than the cells themselves. */

static Word comp(Word A, Word B)
{
      Word s_a,s_b,t;

Step1: /* Initialization. */
      s_a = LELTI(A,SC_SIGN);
      s_b = LELTI(B,SC_SIGN);
      t = 0;

Step2: /* Compare siginitures. */
      while ( t == 0 && s_a != NIL) {
	t = BDCOMP(FIRST(s_a),FIRST(s_b)); 
	s_a = RED(s_a); s_b = RED(s_b); }

Return: /* Return. */
      return (t);
}

/*======================================================================
                     t <- NAIVEDOPFSUFF(P,D,i)

Do the projection factors suffice?

inputs
 P  : Projection factor set data structure.
 D  : The root cell of a full sign-invariant CAD.
 i  : The level of the CAD
outputs
 t  : NIL if no solution formula exists using the pols in P.
      Otherwise, TRUE, FALSE, or UNDET.
      TRUE (FALSE)  if all cells in substrees rooted at cells K which 
      have truth values have truth value TRUE (FALSE).  Otherwise
      UNDET.
======================================================================*/
#include "qepcad.h"

static Word comp(Word A, Word B);
#define BDCOMP(a,b)       ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
	  
Word NAIVEDOPFSUFF(Word P, Word D, Word i)
{
      Word t,L,tc,fc,tf,ff,c1,c2;

Step1: /* Set L to the list of all i-level cells. */
      L = CADCL(D,i);
      if (L == NIL) {
	t = -7;
	goto Return; }

Step2: /* Sort L by signiture. */
      L = GMSL(L,comp);

Step3: /* */
      tc = 0; fc = 0;
      while (L != NIL) {
	tf = 0; ff = 0;
	ADV(L,&c1,&L);
	if (LELTI(c1,TRUTH) == TRUE) tf++; else ff++;
	while(L != NIL && comp(c1,FIRST(L)) == 0) {
	  ADV(L,&c2,&L);
	  if (LELTI(c2,TRUTH) == TRUE) tf++; else ff++; }
	if (tf && ff) {
	  t = NIL;
	  goto Return; }
	if (tf) tc++;
	else    fc++; }

Step4: /* */      
      if (tc && fc)
	t = UNDET;
      else if (tc)
	t = TRUE;
      else
	t = FALSE;

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
      S_a = CINV(LELTI(A,SIGNPF));
      S_b = CINV(LELTI(B,SIGNPF));
      t = 0;

Step2: /* Compare siginitures. */
      while (t == 0 && S_a != NIL) {
	ADV(S_a,&s_a,&S_a); ADV(S_b,&s_b,&S_b);
	while ( t == 0 && s_a != NIL) {
	  t = BDCOMP(FIRST(s_a),FIRST(s_b)); 
	  s_a = RED(s_a); s_b = RED(s_b); } }

Return: /* Return. */
      return (t);
}

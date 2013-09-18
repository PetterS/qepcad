/*======================================================================
                     C <- CFLCELLLIST(L_D)

Conflicting cell list.

Inputs
 L_D: A list of cells of the same level, all of which have the 
      same signiture on all projection factors of lower level.

Outputs
 C  : A list (C_1,...,C_N).  C_i contains the list of all pairs of
      cells (a,b) of level i with identical signiture such that:
      1) a is TRUE and b is false or a is FALSE and b is TRUE or
      2) one of the pair has truth value TRUE (FALSE), and the other
         is an ancestor of a cell with truth value FALSE (TRUE).
======================================================================*/
#include "qepcad.h"

static Word comp(Word A, Word B);
#define BDCOMP(a,b)       ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))

Word CFLCELLLIST(Word L_D)
{
      Word C,r,C_r,L,Lp,T,F,U,c,t,f,u,Fp,Up,h,Cb,Cp,Q;
      /* Time */ Word tm;

Step1: /* Initialize. */
      C = NIL;

Step2: /* Get the children of L_D. */
      L = NIL;
      for(Q = L_D; Q != NIL; Q = RED(Q)) {
	L = CCONC(LELTI(FIRST(Q),CHILD),L); }

Step3: /* Sort by signiture. */
	L = GISL(L,comp);

Step4: /* Loop over each block of cells with same signiture. */
	while (L != NIL) {
	  Lp = NIL;
	  do {
	    Lp = COMP(FIRST(L),Lp);
	    L = RED(L);
	  } while (L != NIL && comp(FIRST(Lp),FIRST(L)) == 0);

Step5: /* Separate into lists of TRUE, FALSE, and UNDET cells. */
	  T = NIL; F = NIL; U = NIL; C_r = NIL;
	  while (Lp != NIL) {
	    ADV(Lp,&c,&Lp);
	    switch (LELTI(c,TRUTH)) {
	    case (TRUE) :  T = COMP(c,T); break;
	    case (FALSE) : F = COMP(c,F); break;
	    case (UNDET) : U = COMP(c,U); break; } }

Step6: /* TRUE/FALSE & TRUE/UNDET combinations. */
	    for(; T != NIL; T = RED(T)) {
	      t = FIRST(T);
	      
	      for(Fp = F; Fp != NIL; Fp = RED(Fp)) {
		f = FIRST(Fp); C_r = COMP(LIST2(t,f),C_r); }
	      
	      for(Up = U; Up != NIL; Up = RED(Up)) {
		u = FIRST(Up);
		h = CATV(u);
		if (h == FALSE || h == UNDET) 
		  C_r = COMP(LIST2(t,u),C_r); } }

Step7: /* FALSE/UNDET combinations. */
	    for(; F != NIL; F = RED(F)) {
	      f = FIRST(F);
	      
	      for(Up = U; Up != NIL; Up = RED(Up)) {
		u = FIRST(Up);
		h = CATV(u);
		if (h == TRUE || h == UNDET) 
		  C_r = COMP(LIST2(f,u),C_r); } }

Step8: /* Recurse on the UNDET cells. */
	  if ( U != NIL )
	    Cb = COMP(C_r,CFLCELLLIST(U));
	  else
	    Cb = LIST1(C_r);
	  

Step9: /* Update C to include the */
	  Cp = NIL;
	  while( C != NIL && Cb != NIL ) {
	    Cp = COMP(CCONC(FIRST(Cb),FIRST(C)),Cp);
	    C = RED(C); Cb = RED(Cb); }
	  Cp = CINV(Cp);
	  if ( C != NIL ) Cp = CCONC(Cp,C);
	  if ( Cb != NIL ) Cp = CCONC(Cp,Cb);
	  C = Cp; }
	  

Return: /* Prepare to return. */
      return (C);
}


	
/*-- Comparison of signitures of cells.  Both cells 
  -- are assumed to be of the same level, and both are assumed
  -- to have identical signiture on all projection factors
  -- of level lower than the cells.  */

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

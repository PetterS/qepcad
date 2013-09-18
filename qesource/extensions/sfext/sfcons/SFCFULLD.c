/*======================================================================
Solution Formula Construction Full Dimensional cells only.

Inputs:
D : a qepcad CAD structure
P : the projection factor set for D
J : the projection polynomial set for D, or possibly a superset
n : the level of the CAD (note that this can be less than the true level)

Side Effects:
A solution formula is written to standard out.  This solution formula
is based exclusively on the truth values of full-dimensional cells, i.e.
leaf cells for which level=dimension.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"
static Word LISTOETAmod(Word P,Word i,Word t);
static Word PLISTOETAmod(Word p,Word B,Word t);

void QepcadCls::SFCFULLD(Word D, Word P, Word J, Word n)
{
      Word t,SF,Dp,Pp,Lt,Lf,LA,Q,D1,P1,D0,P0,J0,i,Lp,pflag, L;
      char e,s,m,c;

Step1: /* Space is either empty or R^n. */
      t = DOPFSUFF_FULLD(P,LIST1(D));
      if (t == TRUE) {       
        SF = LIST1(TRUE);  /* CAD is identically TRUE. */
        goto Step3; }
      else if (t == FALSE) {
        SF = LIST1(FALSE); /* CAD is identically FALSE. */
        goto Step3; }

Step2: /* Extended language. */
      /* Dp,Pp are a simplified CAD for D,P (based only on full-dimensional cells!) */
      CCADCONmod(n,P,D,&Pp,&Dp); 
      Dp = PCAD2ESPCAD(P,Pp,Dp,NIL);

      /* Get list of all the true and false cells. */
      LTFOCALWTV(Dp,n,&Lt,&Lf);

      /* Filter out all but the full-dimensional true/false cells. */
      for(L = NIL; Lt != NIL; Lt = RED(Lt))
	if (LELTI(LELTI(FIRST(Lt),SC_REP),LEVEL) == CELLDIM(LELTI(FIRST(Lt),SC_REP)))
	  L = COMP(FIRST(Lt),L);
      Lt = L;
      for(L = NIL; Lf != NIL; Lf = RED(Lf))
	if (LELTI(LELTI(FIRST(Lf),SC_REP),LEVEL) == CELLDIM(LELTI(FIRST(Lf),SC_REP)))
	  L = COMP(FIRST(Lf),L);
      Lf = L;
	

      if (Lt == NIL && Lf == NIL) {
	SWRITE("No cells have truth values!\n");
	goto Return; }
      t = ESPCADDOPFSUFF(Pp,LIST1(Dp));
      LA = LISTOETAmod(Pp,n,t==NIL);

      /* Construct formula */
      SF = NECCONDS(Lt,Lf,LA,Pp); 
      SF = FMASORT(SF);
      SF = FMA_REMCONST(SF);
      SF = FMASMOOTH(SF);
      SF = FMAOPCOMBINE(SF);

Step3: /* Write formula */
      SWRITE("\nAn equivalent quantifier-free formula:\n\n");
      FMAWRITE(SF,Pp,GVVL);
      SWRITE("\n\n");
      
      
 Return: /* Prepare to return. */
      return;
}



/*
List of extended Tarski atoms (modified to only include atoms involving
>= and <=, i.e. the one's you'd need for full-dim cells only)

P a proj fac set
i a level
t a T/F flag
Returns a list of atoms using the extended stuff if "t" and
otherwise not.  the atoms are only the ones you need if you
only look at full dim cells.
 */
static Word LISTOETAmod(Word P, Word i, Word t)
{
     Word L,n,L_A,p,B;

Step1: /* Construct list of all projection factors, in reverse order. */
     for(L = NIL, n = 1; n <= i; n++)
	 L = CCONC(LELTI(P,n),L);
     L = CINV(L);
     
 Step2: /* */
     for(L_A = NIL; L != NIL; L = RED(L)) {
	 p = FIRST(L);
	 B = PDEG(LELTI(p,PO_POLY));
	 L_A = CCONC(PLISTOETAmod(p,B > 1 ? B : 0,t),L_A); }
     
     return L_A;
}

/*
Polynomial list of extended Tarski atoms. (modified to only include 
atoms involving >= and <=, i.e. the one's you'd need for full-dim cells only)

  p : a QEPCAD polynomial
  B : a bound on the number of roots (need not be a valid bound)
  t : a flag
 */
static Word PLISTOETAmod(Word p, Word B, Word t)
{
    Word L,I,i;

    L = NIL;
    I = RED(LELTI(p,PO_LABEL));

    if (t) {
      for(i = B; i > 0; i--) {
	L = COMP(LIST2(I,LIST2(LEOP,i)),L);
	L = COMP(LIST2(I,LIST2(LEOP,-i)),L);
	
	L = COMP(LIST2(I,LIST2(GEOP,i)),L);
	L = COMP(LIST2(I,LIST2(GEOP,-i)),L); }
    }
    
    L = COMP(LIST2(I,LEOP),L);
    L = COMP(LIST2(I,GEOP),L);
    
    return L;
}


/*======================================================================
                     t <- DOPFSUFF_FULLD(P,D)

Do the projection factors suffice? Full-dimensional cell only version

inputs
 P  : Projection factor set data structure.
 K  : A list of partial CAD cells, all in a CAD defined by P, all of 
      full-dimension, and all with the same signiture.
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
	  
Word DOPFSUFF_FULLD(Word P, Word K)
{
      Word t,L,Kp,Lp,T,F,N,Lpp,tp,H;

Step1: /* Initialize. */
      if (LELTI(FIRST(K),LEVEL) == 0 && LELTI(FIRST(K),CHILD) == NIL) {
	t = LELTI(FIRST(K),TRUTH);
	goto Return; }
      else
	t = NIL;

Step3: /* List full-dimensional cells of level r, sorted by signiture. */
      L = NIL;
      for(Kp = K; Kp != NIL; Kp = RED(Kp))
	for(H = CINV(LELTI(FIRST(Kp),CHILD)); H != NIL; H = RED(H) == NIL ? NIL : RED2(H))
	  L = COMP(FIRST(H),L);
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
	tp = DOPFSUFF_FULLD(P,Lp);
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

Step2: /* Compare signitures. */
	ADV(S_a,&s_a,&S_a); ADV(S_b,&s_b,&S_b);
	while ( t == 0 && s_a != NIL) {
	  t = BDCOMP(FIRST(s_a),FIRST(s_b)); 
	  s_a = RED(s_a); s_b = RED(s_b); }

Return: /* Return. */
      return (t);
}

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
#include "espcad.h"

Word ESPCADDOPFSUFF_FULLD(Word P, Word K)
{
      Word t,L,Kp,Lp,T,F,Lpp,tp,C,H;

Step1: /* Initialize. */
      if (LELTI(FIRST(K),LEVEL) == 0 && LELTI(FIRST(K),CHILD) == NIL) {
	t = LELTI(FIRST(K),TRUTH);
	goto Return; }
      else
	t = NIL;

Step3: /* List cells of level r, sorted by signiture. */
      L = NIL;
      for(Kp = K; Kp != NIL; Kp = RED(Kp))
      {
	C = LELTI(FIRST(Kp),SC_CDTV);
	if (ISLIST(C)) {
	  for(H = CINV(C); H != NIL; H = RED(H) == NIL ? NIL : RED2(H))
	    L = COMP(FIRST(H),L); }
      }
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
	  if ( T == 0 && F == 0 ) { tp = NA; goto Step8; }
	  if ( T > 0 && F == 0 )  { tp = TRUE; goto Step8; }
	  if ( F > 0 && T == 0 )  { tp = FALSE; goto Step8; }
	  t = NIL; goto Return; }

Step7: /* Case:  Not all cells are leaf cells. */
	tp = ESPCADDOPFSUFF_FULLD(P,Lp);
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


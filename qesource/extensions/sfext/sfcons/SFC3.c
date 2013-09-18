/*======================================================================
Solution Formula Construction

Inputs:
D : a qepcad CAD structure
P : the projection factor set for D
J : the projection polynomial set for D, or possibly a superset
n : the level of the CAD (note that this can be less than the true level)
L : a list of options of the form (e,s,m), where e in {0,1}, s in {0,1}
    and m in {0,1,2}

Side Effects:
A solution formula is written to standard out.

Note:  Right now, if there are cells of level n without truth value,
       I have no idea what will happen when simplification is attempted.

======================================================================*/
#include "qepcad.h"

void QepcadCls::SFC3(Word D, Word P, Word J, Word n, Word L)
{
      Word t,SF,e,s,m,Dp,Pp,Lt,Lf,LA,Q,D1,P1,D0,P0,J0,i,Lp,pflag;

Step1: /* Space is either empty or R^n. */
      t = DOPFSUFF(P,LIST1(D));
      if (t == TRUE) {       
        SF = LIST1(TRUE);  /* CAD is identically TRUE. */
        goto Step4; }
      else if (t == FALSE) {
        SF = LIST1(FALSE); /* CAD is identically FALSE. */
        goto Step4; }

      FIRST3(L,&e,&s,&m);
      if (e) {
Step2: /* Extended language. */

	/* Construct the CAD on which we'll operate. */
	if (s) { /* No simplification. */
	  Dp = SCADDSCON(D,NIL,n);
	  Pp = P; }
	else { /* Simplify! */
	  CCADCON(n,P,D,&Pp,&Dp); }
	Dp = PCAD2ESPCAD(P,Pp,Dp,NIL);

	/* Initialization. */
	LTFOCALWTV(Dp,n,&Lt,&Lf);
	if (Lt == NIL && Lf == NIL) {
	  SWRITE("No cells have truth values!\n");
	  goto Return; }
	Lt = SPCADCBDD(Lt,n); /* sort true cells by decreasing dimension. */
	LA = LISTOETA(Pp,n);

	/* Actually construct formula. */
	switch(m) {
	case (0) : SF = NECCONDS(Lt,Lf,LA,Pp); break;
	case (1) : SF = NAIVESF(Lt,Lf,LA,Pp); break;
	case (2) : SF = GEOTEST(Dp,Pp,n,LA); break; }
      }
      else {

Step3: /* The normal language. */
	
	/* Do we have projection definability? */
	if (t == NIL) { /* No we don't! */
	  D0 = GVPC; P0 = LCOPY(GVPF); J0 = LCOPY(GVPJ);
	  for(i = GVNFV - LENGTH(J0); i > 0; i--)
	    J0 = INV(COMP(NIL,INV(J0)));
	  STRIPPED_BIGLOOP(J0,P0,P0,D0,GVNFV,&P1,&D1); }
	else {
	  D1 = D; P1 = P; }
	
	/* Construct the CAD on which we'll operate. */
	if (s) { /* No simplification. */
	  Dp = SCADDSCON(D1,NIL,n);
	  Pp = P1; }
	else { /* Simplify! */
	  CCADCON(n,P1,D1,&Pp,&Dp); 
	  t = ESPCADDOPFSUFF(Pp,LIST1(Dp));
	  if (t == NIL) {
	    Q = MINPFSET(P1,Pp,D1,n);
	    CCADCONFPFS(n,P1,D1,Q,&Pp,&Dp); } }
	Dp = PCAD2ESPCAD(P1,Pp,Dp,NIL);

	LTFOCALWTV(Dp,n,&Lt,&Lf);
        Lt = SPCADCBDD(Lt,n);
        LA = LISTOTA(Pp,n);

	/* Actually construct formula. */
	switch(m) {
	case (0) : SF = NECCONDS(Lt,Lf,LA,Pp); break;
	case (1) : SF = NAIVESF(Lt,Lf,LA,Pp); break; 
	case (2) : SWRITE("GEOTEST requires the extended language!\n"); goto Return; } }

Step4: /* Massage the formula. */
      pflag = 1;
      for(Lp = RED3(L); Lp != NIL || pflag; Lp = RED(Lp)) {
	if (Lp == NIL) { Lp = LIST1(-1); }
	if (FIRST(Lp) < 0) pflag = 0;
	switch(FIRST(Lp)) {
	case 0: /* FMASORT */
	  SF = FMASORT(SF);
	  break; 
	case 1: /* FMA_REMCONST */
	  SF = FMA_REMCONST(SF);
	  break;
	case 2: /* FMASMOOTH */
	  SF = FMASMOOTH(SF);
	  break;
	case 3: /* FMAOPCOMBINE */
	  SF = FMAOPCOMBINE(SF);
	  break;
	case 4: /* FMATRYDISTRIBUTE */
	  SF = FMATRYDISTRIBUTE(SF);
	  break;
	case 5: /* FMASTRENGTHEN */
	  FMASTRENGTHEN(SF,Lt,Pp); /* SF may get modified! */
	  break;

	case -1: /* Normal output. */
	  SWRITE("\nAn equivalent quantifier-free formula:\n\n");
	  FMAWRITE(SF,Pp,GVVL);
	  SWRITE("\n\n");
	  break;
	case -2: /* Using P_x,y notation. */
	  SWRITE("\nAn equivalent quantifier-free formula:\n\n");
	  FMAWRITEp(SF,Pp,GVVL,0);
	  SWRITE("\n\n");
	  break;
	case -3: /* Output in latex format. */
	  SWRITE("\nAn equivalent quantifier-free formula:\n\n");
	  FMAWRITELATEX(SF,Pp,GVVL);
	  SWRITE("\n\n");
	  break;
	case -4: /* Printing over multiple lines. */
	  SWRITE("\nAn equivalent quantifier-free formula:\n\n");
	  FMAWRITENEWLINE(SF,Pp,GVVL,0);
	  SWRITE("\n\n");
	  break;
	case -5: /* */
	  FMAWRITEQEIN(SF,Pp,GVVL);
	  SWRITE("\n\n");
	  break; } }
	
Return: /* Prepare to return. */
      return;
}

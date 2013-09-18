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

static char LANGCHOICE(Word *L_, Word t);
static char SIMPLECHOICE(Word *L_);
static char SFALGCHOICE(Word *L_, char e);
static void print_stats(Word L);
static Word T1; /* Time for DOPFSUFF in Step 1. */
static Word T2; /* Time for CAD Simplification. */
static Word T3; /* Time for formula construction alg. */
static Word T4; /* Time for `putting back' p.f.'s. */
static Word F1; /* Flag indicating that p.f.'s were put back. */

void QepcadCls::SFC4(Word D, Word P, Word J, Word n, Word L)
{
      Word t,SF,Dp,Pp,Lt,Lf,LA,Q,D1,P1,D0,P0,J0,i,Lp,pflag;
      char e,s,m,c;
      T1 = T2 = T3 = T4 = 0;
      F1 = 0;

Step1: /* Space is either empty or R^n. */
          T1 = ACLOCK();
      t = DOPFSUFF(P,LIST1(D));
          T1 = ACLOCK() - T1;
      if (t == TRUE) {       
        SF = LIST1(TRUE);  /* CAD is identically TRUE. */
        goto Step4; }
      else if (t == FALSE) {
        SF = LIST1(FALSE); /* CAD is identically FALSE. */
        goto Step4; }

      e = LANGCHOICE(&L,t);
      if (e == 'E') {
Step2: /* Extended language. */

	/* Construct the CAD on which we'll operate. */
	s = SIMPLECHOICE(&L);
	if (s == 'N') { /* No simplification. */
	  Dp = SCADDSCON(D,NIL,n);
	  Pp = P; }
	else { /* Simplify! */
	      T2 = ACLOCK();
	  CCADCON(n,P,D,&Pp,&Dp); 
	      T2 = ACLOCK() - T2;
	}
	Dp = PCAD2ESPCAD(P,Pp,Dp,NIL);

	/* Initialization. */
	LTFOCALWTV(Dp,n,&Lt,&Lf);
	if (Lt == NIL && Lf == NIL) {
	  SWRITE("No cells have truth values!\n");
	  goto Return; }
	Lt = SPCADCBDD(Lt,n); /* sort true cells by decreasing dimension. */
	LA = LISTOETA(Pp,n);

	/* Actually construct formula. */
	m = SFALGCHOICE(&L,e);
	switch(m) {
	case 'N' : 
	      T3 = ACLOCK();
	  SF = NECCONDS(Lt,Lf,LA,Pp); 
	      T3 = ACLOCK() - T3;
	  break;
	case 'S' : 
	      T3 = ACLOCK();
	  SF = NAIVESF(Lt,Lf,LA,Pp); 
	      T3 = ACLOCK() - T3;
	  break;
	case 'G' : 
	      T3 = ACLOCK();
	  SF = GEOTEST(Dp,Pp,n,LA); 
	      T3 = ACLOCK() - T3;
	  break; }
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
	s = SIMPLECHOICE(&L);
	if (s == 'N') { /* No simplification. */
	  Dp = SCADDSCON(D1,NIL,n);
	  Pp = P1; }
	else { /* Simplify! */
	      T2 = ACLOCK();
	  CCADCON(n,P1,D1,&Pp,&Dp); 
	      T2 = ACLOCK() - T2;
	  t = ESPCADDOPFSUFF(Pp,LIST1(Dp));
	  if (t == NIL) {
	        F1 = 1;
	        T4 = ACLOCK();
	    Q = MINPFSET(P1,Pp,D1,n);
	    CCADCONFPFS(n,P1,D1,Q,&Pp,&Dp); 
	        T4 = ACLOCK() - T4;
	  } }
	Dp = PCAD2ESPCAD(P1,Pp,Dp,NIL);

	LTFOCALWTV(Dp,n,&Lt,&Lf);
        Lt = SPCADCBDD(Lt,n);
        LA = LISTOTA(Pp,n);

	/* Actually construct formula. */
	m = SFALGCHOICE(&L,e);
	switch(m) {
	case 'N' : 
	      T3 = ACLOCK();
	  SF = NECCONDS(Lt,Lf,LA,Pp); 
	      T3 = ACLOCK() - T3;
	  break;
	case 'S' : 
	      T3 = ACLOCK();
	  SF = NAIVESF(Lt,Lf,LA,Pp); 
	      T3 = ACLOCK() - T3;
	  break; } }


Step4: /* Massage the formula. */
      while (1) {
	SWRITE("Enter Options P,I,L,M,or Q to print formula, or\n");
	SWRITE("Enter Options S,R,Z,C, D or A to modify the formula, or\n");
	SWRITE("Enter Option H for help, T for timing, or '.' to quit.\n: ");
	if (!((c = CREADB()) && c != '.')) break;
	switch(c) {
	case 'S': /* FMASORT */
	  SF = FMASORT(SF);
	  break; 
	case 'R': /* FMA_REMCONST */
	  SF = FMA_REMCONST(SF);
	  break;
	case 'Z': /* FMASMOOTH */
	  SF = FMASMOOTH(SF);
	  break;
	case 'C': /* FMAOPCOMBINE */
	  SF = FMAOPCOMBINE(SF);
	  break;
	case 'D': /* FMATRYDISTRIBUTE */
	  SF = FMATRYDISTRIBUTE(SF);
	  break;
	case 'A': /* FMASTRENGTHEN */
	  FMASTRENGTHEN(SF,Lt,Pp);
	  break;
 
	case 'P': /* Normal output. */
	  SWRITE("An equivalent quantifier-free formula:\n\n");
	  FMAWRITE(SF,Pp,GVVL);
	  SWRITE("\n\n");
	  break;
	case 'I': /* Using P_x,y notation. */
	  SWRITE("An equivalent quantifier-free formula:\n\n");
	  FMAWRITEp(SF,Pp,GVVL,0);
	  SWRITE("\n\n");
	  break;
	case 'L': /* Output in latex format. */
	  SWRITE("An equivalent quantifier-free formula:\n\n");
	  FMAWRITELATEX(SF,Pp,GVVL);
	  SWRITE("\n\n");
	  break;
	case 'M': /* Printing over multiple lines. */
	  SWRITE("An equivalent quantifier-free formula:\n\n");
	  FMAWRITENEWLINE(SF,Pp,GVVL,0);
	  SWRITE("\n\n");
	  break;
	case 'Q': /* Print as QEPCAD input. */
	  FMAWRITEQEIN(SF,Pp,GVVL);
	  SWRITE("\n\n");
	  break;
	  
	case 'T': /* Print Stats. */
	  print_stats(LIST3(e,s,m));
	  break;

	case 'H': /* Help. */
	  SWRITE("Print Options:\n");
	  SWRITE("P - Prints formula in the usual syntax.\n");
	  SWRITE("I - Prints formula using projection factor indices.\n");
	  SWRITE("L - Prints formula in LaTeX format.\n");
	  SWRITE("M - Prints formula over multiple lines.\n");
	  SWRITE("Q - Prints formua in QEPCAD input format.\n");
	  SWRITE("T - Prints timing statistics for fomula construction.\n");
	  SWRITE("\nFormula Modification Options:\n");
	  SWRITE("S - Sorts the formula.\n");
	  SWRITE("R - Removes the constants TRUE and FALSE from formula.\n");
	  SWRITE("Z - \"Smooths\" the formula - i.e. flattens it.\n");
	  SWRITE("C - Combines p > 0 /\\ p < 0 into P /= 0.\n\n");
	  SWRITE("D - Tries to simplify by distributing atomic formulas.\n");
	  SWRITE("A - Tries to strenghten inequalities in atoms of the formula.\n");
	  break;
	default:
	  SWRITE("Option ");
	  CWRITE(c);
	  SWRITE(" is not understood!\n\n");
	  break; } }
      
      
 Return: /* Prepare to return. */
      return;
}


static char LANGCHOICE(Word *L_, Word t)
{
  char c;
  Word L;

  /* Initialize. */
  L = *L_;

  if (L != NIL) {
    /* Option is taken from list L. */
    c = (char)FIRST(L);
    L = RED(L); }

  else {
    /* Option is read in from user. */
    do {
      if (t == NIL) SWRITE("Note: CAD is NOT projection definable!\n");
      else          SWRITE("Note: CAD IS projection definable!\n");
      SWRITE("Formula Language [T = Tarski, E = Extended]: ");
      c = CREADB();
    if (c == 'T' || c == 'E') break;
      SWRITE("Option must be 'T' or 'E'!!\n");
    } while(1); }
  
  /* Update L_ and return. */
  *L_ = L;
  return c;
}


static char SIMPLECHOICE(Word *L_)
{
  char c;
  Word L;

  /* Initialize. */
  L = *L_;

  if (L != NIL) {
    /* Option is taken from list L. */
    c = (char)FIRST(L);
    L = RED(L); }

  else {
    /* Option is read in from user. */
    do {
      SWRITE("CAD Simplification [Y = Use it, N = Don't use it]: ");
      c = CREADB();
    if (c == 'Y' || c == 'N') break;
      SWRITE("Option must be 'Y' or 'N'!!\n");
    } while(1); }
  
  /* Update L_ and return. */
  *L_ = L;
  return c;
}


static char SFALGCHOICE(Word *L_, char e)
{
  char c;
  Word L;

  /* Initialize. */
  L = *L_;

  if (L != NIL) {
    /* Option is taken from list L. */
    c = (char)FIRST(L);
    L = RED(L); }

  else if (e == 'E') {
    /* Option for Extended Language is read in from user. */
    do {
      SWRITE("S.F. Construction Algorithm\n");
      SWRITE("[S = SIMPLESF, N = Necessary Conditions, G = GEOFORM] : ");
      c = CREADB();
    if (c == 'S' || c == 'N' || c == 'G') break;
      SWRITE("Option must be 'S', 'N', or 'G'!!\n");
    } while(1); }
  
  else {
    /* Option for Tarski Language is read in from user. */
    do {
      SWRITE("S.F. Construction Algorithm\n");
      SWRITE("[S = SIMPLESF, N = Necessary Conditions] : ");
      c = CREADB();
    if (c == 'S' || c == 'N') break;
      SWRITE("Option must be 'S' or 'N'!!\n");
    } while(1); }
  
  /* Update L_ and return. */
  *L_ = L;
  return c;
}

static void print_stats(Word L)
{
  Word e,s,m;
  FIRST3(L,&e,&s,&m);

  SWRITE("\n************************************************\n\n");

  SWRITE("Initial check (TRUE,FALSE,PDEF,unPDEF): ");
  IWRITE(T1);
  SWRITE("\n");

  if (s == 'Y') {
    SWRITE("CAD Simplification: ");
    IWRITE(T2);
    SWRITE("\n"); }

  if (F1) {
    SWRITE("`Putting back' projection factors: ");
    IWRITE(T4);
    SWRITE("\n"); }

  SWRITE("Formula construction algorithm ");
  switch (m) {
  case 'S': SWRITE("SIMPLESF: "); break;
  case 'N': SWRITE("NECCONDS: "); break;
  case 'G': SWRITE("GEOFORM: "); break; }
  IWRITE(T3);
  SWRITE("\n");

  SWRITE("\n************************************************\n");
  return;
}

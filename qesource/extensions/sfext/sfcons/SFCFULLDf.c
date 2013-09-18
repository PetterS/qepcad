/*======================================================================
Solution Formula Construction Full Dimensional cells only.(formula returned)

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

Word QepcadCls::SFCFULLDf(Word D, Word P, Word J, Word n)
{
      Word t,SF,Dp,Pp,Lt,Lf,LA,Q,D1,P1,D0,P0,J0,i,Lp,pflag, L;
      char e,s,m,c;

Step1: /* Space is either empty or R^n. */
      t = DOPFSUFF_FULLD(P,LIST1(D));
      if (t == TRUE) {       
        SF = LIST1(TRUE);  /* CAD is identically TRUE. */
        goto Return; }
      else if (t == FALSE) {
        SF = LIST1(FALSE); /* CAD is identically FALSE. */
        goto Return; }

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

 Return: /* Prepare to return. */
      return SF;
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


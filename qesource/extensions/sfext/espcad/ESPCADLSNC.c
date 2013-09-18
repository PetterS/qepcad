/*======================================================================
                      L <- ESPCADLSNC(D,P,i)

ESPCAD list of strong necessary conditions.

Inputs
  D : an ESPCAD.
  P : the projection factor set to which D's signatures refer
  i : a positive BETA-digit.

Output
  L : a list of strong necessary conditions.  An atomic formula is a
      strong necessary condition if it is satisfied in every "true
      cell, and if there is a false cell which differs from some true
      cell solely by this condition.  Some of the conditions may be
      redundant.  Truth of a cell is based on the "temporary mark" 
      field.
======================================================================*/
#include "espcad.h"

/* a and b are atomic formulas, but ICOMP is used to do the dirty work. */
static Word comp(Word a, Word b)
{
  Word t;
  t = ICOMP(FIRST(a),FIRST(b));
  if (!t)
    t = ICOMP(SECOND(a),SECOND(b));
  return t;
}

Word ESPCADLSNC(Word D, Word P, Word i)
{
      Word Q,C,T,L,Lp,A,t,R,Rp,r,c1,c2,c3,S;

Step1: /* Construct Q, a list of (i-1)-level cells. */
      Q = PCADCL(D,i-1);

Step2: /* Loop over each cell C in Q. */
      for(L = NIL; Q != NIL; Q = RED(Q)) {
	C = FIRST(Q);
	if (ISATOM(LELTI(C,SC_CDTV)))
	  continue;

Step3: /* Remove from L any condition that is not necessary over C. 
	for(Lp = CINV(L), S = NIL; Lp != NIL; Lp = RED(Lp)) {
	  A = FIRST(Lp);
	  for(t = 1, R = LELTI(C,SC_CDTV); t && R != NIL; R = RED(R)) {
	    r = FIRST(R);
	    t = (LELTI(r,SC_TMPM) != TRUE || FMACELLEVAL(A,r) == TRUE); }
	  if (t)
	    S = COMP(A,S); } */

Step4: /* Construct T, a list of necessary conditions over C. */
	R = LELTI(C,SC_CDTV);
	T = NIL;
	for(ADV(R,&c1,&R); R != NIL; c1 = c3) {
	  ADV2(R,&c2,&c3,&R);
	  T = CONC(ESPCADCTLSNC(c1,c2,c3,i,P),T); }
	    
Step5: /* Merge T and L. */
	L = GMSDSL(CCONC(T,L),comp); }

Step6: /* Remove from L any condition that is not necessary. */
      R = PCADCL(D,i);
      for(Lp = CINV(L), S = NIL; Lp != NIL; Lp = RED(Lp)) {
	A = FIRST(Lp);
	for(t = 1, Rp = R; t && Rp != NIL; Rp = RED(Rp)) {
	    r = FIRST(Rp);
	    t = (LELTI(r,SC_TMPM) != TRUE || FMACELLEVAL(A,P,r) == TRUE); }
	  if (t)
	    S = COMP(A,S); }
      L = S;


Return: /* */
      return L;
}  
      

/*======================================================================
                      L <- ESPCADCTLSNC(c1,c2,c3,i,P)

ESPCAD cell triple list of strong necessary conditions.

Inputs
  c1,c2,c3 : consecutive ESPCAD cells in a stack, c2 a section cell.
  i : the level of c1, c2, and c3.

Output
  L : a list of strong necessary conditions.  An atomic formula is a
      strong necessary condition if it is satisfied in every "true
      cell, and if there is a false cell which differs from some true
      cell solely by this condition.  Some of the conditions may be
      redundant.  Truth of a cell is based on the "temporary mark" 
      field.
======================================================================*/

Word ESPCADCTLSNC(Word c1,Word c2,Word c3,Word i,Word P)
{
      Word S1,S2,S3,n,Sp1,Sp2,s1,s2,T,L,j,k;

Step1: /* Initialize. */
      if (LELTI(c1,SC_TMPM) == LELTI(c2,SC_TMPM) && 
	  LELTI(c1,SC_TMPM) == LELTI(c3,SC_TMPM)) {
	L = NIL;
	goto Return; }
      S1 = LELTI(c1,SC_SIGN);
      S2 = LELTI(c2,SC_SIGN);
      S3 = LELTI(c3,SC_SIGN);

Step2: /* Figure out which polynomials are zero in c2. */
      for(n = 0, Sp1 = S1, Sp2 = S2, T = NIL; n < LENGTH(S1); n++) {
	ADV(Sp1,&s1,&Sp1);
	ADV(Sp2,&s2,&Sp2);
	if (s1 != 0 && s2 == 0)
	  T = COMP(n+1,T); }
  
Step3: /* Loop over each polynomial in T and create condition. */
      for(L = NIL; T != NIL; T = RED(T)) {
	j = FIRST(T);
	k = LELTI(LELTI(c2,SC_EXTS),j)/2;
	L = CONC(ESPCADCTPILSNC(c1,c2,c3,i,j,k,P),L); }
   
Return: /*  */
      return L;
}

/* ESPCAD cell triple and polynomial index list of strong necessary conditions. */
Word ESPCADCTPILSNC(Word c1,Word c2, Word c3, Word i, Word j,Word k, Word P)
{
  Word Lt,Lf,C,c,A,tt,tf,L,Lp,Ls;

Step1: /* Classify cells as true or false. */
  C = LIST3(c1,c2,c3);
  for(Lt = NIL, Lf = NIL; C != NIL; C = RED(C)) {
    c = FIRST(C);
    switch(LELTI(c,SC_TMPM)) {
    case TRUE:  Lt = COMP(c,Lt); break;
    case FALSE: Lf = COMP(c,Lf); break;
    default: break; } }

Step2: /* Need a true cell and a false cell to continue. */
  if (Lt == NIL || Lf == NIL) {
    L = NIL;
    goto Return; }

Step3: /* Weed out conditions that are not strong & necessary. */
  Ls = FMAAFPIRN(i,j,k);
  for(L = NIL; Ls != NIL; Ls = RED(Ls)) {
    A = FIRST(Ls);
    for(tt = 1, Lp = Lt; tt && Lp != NIL; Lp = RED(Lp))
      tt = FMACELLEVAL(A,FIRST(Lp),P);
    for(tf = 1, Lp = Lf; tf && Lp != NIL; Lp = RED(Lp))
      tf = FMACELLEVAL(A,FIRST(Lp),P);
    if (tt && !tf)
      L = COMP(A,L); }

Return: /* */
  return L;
}

/* Formula atoms from polynomial index and root number. */

Word FMAAFPIRN(Word i, Word j, Word k)
{
  Word L,op;
  L = NIL;
  for(op = 1; op <= 6; op++) {
    L = COMP(LIST2(LIST2(i,j),op),L);
    L = COMP(LIST2(LIST2(i,j),LIST2(op,k)),L); }
  return L;
}

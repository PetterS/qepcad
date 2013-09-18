/*
C : an ESPCAD
P : the projection factor set for C
k : a level in C
A : a list of atoms from which to construct a formula
 */
#include "qepcad.h"
#include "espcad.h"
/*======================================================================
                        L <- GEODATA(c,A,P)
GEODATA constructor.

Input:
c:  an ESPCAD cell
A:  a list of atoms
P:  the projection factor set for the CAD in which c resides, and
    the polynomials referred to by the elements of A.

Output
L:  the GEODATA data-structure for Q = {c}, i.e. the list (Q,C_Q,Ap,R,T)

	  xQ    : a set of (k-1)-level cells
	  xC_Q  : the children of the elements of Q
	  xAp   : the atoms that are non-constant in the stack 
	          over each element of Q
	  xR    : the minhitset problem for Q
	  xT    : the biggest hitting set
======================================================================*/
#define xQ   1
#define xC_Q 2
#define xAp  3
#define xR   4
#define xT   5

Word GEODATA(Word c, Word A, Word P)
{
      Word R,T,Q,C_Q,L,Ap;
      R = SRTI(c,P);
      T = LSUNION(R);
      Q = LIST1(c);
      C_Q = LELTI(c,SC_CDTV);
      Ap = ATOMFILTER(A,C_Q,P);
      L = LIST5(Q,C_Q,Ap,R,T);
      return L;
}


/*======================================================================
                 h <- GEOHEURISTIC(a,b)

GEOHEURISTIC

Inputs
a,b: espcad cells of the same level.

Outputs
h: a non-negative heuristic number that roughly indicates "closeness".
   The smaller the number, the "closer" the cells.
======================================================================*/
Word GEOHEURISTIC(Word a, Word b)
{
  Word A,B,x,y;

  A = LELTI(a,SC_PAR);

  /* Both are the 0-level cell. */
  if (A == NIL)
    return 0;

  B = LELTI(b,SC_PAR);
  x = GEOHEURISTIC(A,B);
  y = absm(LELTI(a,SC_INX) - LELTI(b,SC_INX));

  /* Both cells are in the same stack. */
  if (x == 0)
    return y;

  /* The base cells are "very close". */
  if (x == 1)
    return y;

  return 4*x + y;
}

Word GEOMERGE(Word c,Word G,Word P)
{
  Word Q,Qp,C_Q,C_Qp,Ap,App,R,Rp,T,Tp,Rpp;
  FIRST5(G,&Q,&C_Q,&Ap,&R,&T);
  FIRST5(c,&Qp,&C_Qp,&App,&Rp,&Tp);
  Tp = SINTER(Tp,T);
  Rpp = CCONC(Rp,R);
  C_Qp = CCONC(C_Qp,C_Q);
  App  = ATOMFILTER(Ap,C_Qp,P);
  Q = COMP(FIRST(Qp),Q);
  Ap = App;
  C_Q = C_Qp; 
  R = Rpp;
  T = Tp;
  return LIST5(Q,C_Q,Ap,R,T);
}

Word GEOFIT(Word c,Word G,Word P)
{
  Word Q,Qp,C_Q,C_Qp,Ap,App,R,Rp,T,Tp,t,Rpp,A,m,L,x,a;
  FIRST5(G,&Q,&C_Q,&Ap,&R,&T);
  FIRST5(c,&Qp,&C_Qp,&App,&Rp,&Tp);
  Tp = SINTER(Tp,T);
  Rpp = CCONC(Rp,R);
  if (!ISHITSET(Tp,Rpp))
    return 0;
  C_Qp = CCONC(C_Qp,C_Q);
  App  = ATOMFILTER(Ap,C_Qp,P);
  t = LALCFEQ(App,C_Qp,P);
  if (!t) {
    //if (PCVERBOSE) { SWRITE("*\n"); }
    return 0; }
  /* Get a number! */
  a = FIRST(Qp);
  m = 0;
  for(L = Q; L != NIL; L = RED(L)) {
    x = GEOHEURISTIC(a,FIRST(L));
    if (m == 0 || x < m)
      m = x; }
  if (m == 0)
    m = 1;
  return m;
}

Word GEOTEST(Word C,Word P,Word k,Word A)
{
       Word L,Lp,c,S,t,G,Q,Ap,Qp,App,C_Q,C_Qp,SF,SF1,
	    SF2,Lt,Lf,Si,Fi,T,R,Tp,Rp,Rpp,Bs,Bi,i,s,t1,t2,SFp,Ap1,Ap2,a;

Step1: /* Set L to a list of all (k-1)-level cells over which there are
k-level cells with SC_TMPM of TRUE. */
       if (k == 0) {
	 SF = LIST1(TRUE);
	 goto Return; }
       SF = NIL;
       L = NIL;
       for(Lp = PCADCL(C,k-1); Lp != NIL; Lp = RED(Lp)) {
	 c = FIRST(Lp); S = LELTI(c,SC_CDTV); if (!ISLIST(S)) continue;
	 for(t = 0; S != NIL && !t; S = RED(S))
	   t = (LELTI(FIRST(S),SC_TMPM) == TRUE);
	 if (t)
	   L = COMP(c,L); }

Step2: /* Set G to a decomposition of L. */
       G = NIL;
       L = SPCADCBDD(L,k-1);
       G = LIST1(GEODATA(FIRST(L),A,P));
       L = RED(L);
       while(L != NIL) {
	 c = GEODATA(FIRST(L),A,P);
	 L = RED(L);
	 Bs = 0;
	 Bi = 0;
	   
	 for(i = LENGTH(G); i > 0; i--) {
	   s = GEOFIT(c,LELTI(G,i),P);
	   if (s != 0 && (Bs == 0 || s < Bs)) {
	     Bs = s;
	     Bi = i; } }
	 
	 if (Bi == 0)
	   G = COMP(c,G);
	 else
	   SLELTI(G,Bi,GEOMERGE(c,LELTI(G,Bi),P)); }


Step3: /* Use the partition to construct the formula. */
       for(SF = NIL; G != NIL; G = RED(G)) {
	 FIRST3(FIRST(G),&Q,&C_Q,&Ap);

T = LBIBMS(LELTI(FIRST(G),5));
Ap1 = NIL; Ap2 = NIL;
for(App = CINV(Ap); App != NIL; App = RED(App)) {
  a = FIRST(App);
  i = POLINDEX2SIGINDEX(LELTI(P,k),SECOND(FIRST(a)));
  if (MEMBER(i,T))
    Ap1 = COMP(a,Ap1);
  else
    Ap2 = COMP(a,Ap2); }
Ap = CCONC(Ap1,Ap2);


	 /* Separate C_Q into T and F, the TRUE and FALSE cells. */
	 for(Lt = NIL, Lf = NIL; C_Q != NIL; C_Q = RED(C_Q)) {
	   c = FIRST(C_Q);
	   if (LELTI(c,SC_TMPM) == TRUE)
	     Lt = COMP(c,Lt);
	   else
	     Lf = COMP(c,Lf); }

	 /* Construct a formula. */
	 SF1 = NAIVESF(Lt,Lf,Ap,P);
	 
	 /* Construct formula for base. */
	 ESCSLKMF(C,k-1);
	 for(Qp = Q; Qp != NIL; Qp = RED(Qp))
	   SLELTI(FIRST(Qp),SC_TMPM,TRUE);
	 SF2 = GEOTEST(C,P,k-1,A);

	 /* Combine Formulas. */
	 t2 = FTYPEINFO(SF2);
	 t1 = FTYPEINFO(SF1);
	 if (t1 == TRUE)
	   SF = COMP(SF2,SF);
	 else if (t2 == TRUE)
	   SF = COMP(SF1,SF);
	 else
	   SF = COMP(LIST3(ANDOP,SF2,SF1),SF);

       }

Step4: /* Convert SF from a list of formulas to a formula. */
       if (LENGTH(SF) > 1)
	 SF = COMP(OROP,SF);
       else
	 SF = FIRST(SF);

Return: /* Prepare to Return. */
   return SF;
}


/* Sublist of L_A consisting of all atoms that take on both true and
   false values on the elements in L_C
   */
Word ATOMFILTER(Word L_A,Word L_C,Word P)
{
       Word L,A,t,f,a,v,C;

Step1: /* Loop over each atom. */
       L = NIL;
       for(A = CINV(L_A); A != NIL; A = RED(A)) {
	 t = 0;
	 f = 0;
	 a = FIRST(A);
	 
	 for(C = L_C; C != NIL; C = RED(C)) {
	   v = FMACELLEVAL(a,FIRST(C),P);
	   if (v == TRUE) t++;
	   else if (v == FALSE) f++; }
	 
	 if (t && f)
	   L = COMP(a,L); }
       
Return: /* Prepare to return. */
       return L;
}

/*
  Returns TRUE if a formula using L_A exists, FALSE otherwise.
List of atoms, list of cells, formula existence query.
 */
Word LALCFEQ(Word L_A,Word L_C,Word P)
{
       Word t,L,v,T,F,a,c;

Step1: /* Base case. */
       if (L_A == NIL) {
	 t = LELTI(FIRST(L_C),SC_TMPM);
	 for(L = RED(L_C); L != NIL && t == LELTI(FIRST(L),SC_TMPM); L = RED(L));
	 if (L == NIL)
	   v = TRUE;
	 else
	   v = FALSE; }
       else {

Step2: /* Recurse. */
         T = NIL;
	 F = NIL;
	 a = FIRST(L_A);
	 for(L = L_C; L != NIL; L = RED(L)) {
	   c = FIRST(L);
	   switch(FMACELLEVAL(a,c,P)) {
	   case TRUE:  T = COMP(c,T); break;
	   case FALSE: F = COMP(c,F); break;
	   case UNDET: T = COMP(c,T);  F = COMP(c,F); break; } }
	 if (T != NIL && F == NIL)
	   v = LALCFEQ(RED(L_A),T,P);
	 if (T == NIL && F != NIL)
	   v = LALCFEQ(RED(L_A),F,P);
	 if (T != NIL && F != NIL)
	   v = (LALCFEQ(RED(L_A),T,P) && LALCFEQ(RED(L_A),F,P)); }
       
Return: /* Prepare to return. */
       return v;
}


/*
F : a formula in DNF form (formally speaking!) involving k-level p.f.'s
S : a set of cells in k-1 space.  F is a formula for the children of the
    elements of S.
P : the projection factor set on which the signitures of cells are based.
Fs: a list of disjuncts that are satisfied for some element above each cell
    in S.

Output
L : a list of pairs (S_i,F_i), the S_i represent a partition of S.  Over 
    each cell in S_i there is a child cell satisfying F_i.  F_i is in
    DNF form (formally speaking!).
 */

Word GEOPART(Word F,Word S,Word P,Word Fs)
{
  Word L,f,Fp,St,Sf,Sp,Lt,Lf;

  /* Base Case. */
  if (LENGTH(F) == 1) { /* i.e. (OROP). */
    L = LIST1(LIST2(S,CCONC(F,Fs)));
    goto Return; }
  
  /* f is the first disjunct, Fp is the formula with f removed. */
  f = SECOND(F);
  Fp = COMP(OROP,RED2(F));
  
  /* Partition S into St and Sf, elt's  with a child that 
     satisfies f and those without. */
  for(St = NIL, Sf = NIL, Sp = S; Sp != NIL; Sp = RED(Sp)) 
    if (FMACELLEXQ(f,FIRST(Sp),P))
      St = COMP(FIRST(Sp),St);
    else
      Sf = COMP(FIRST(Sp),Sf);

  /* If needed, decompose St. */
  if (St == NIL)
    Lt = NIL;
  else
    Lt = GEOPART(Fp,St,P,COMP(f,Fs));

  /* If needed, decompose Sf. */
  if (Sf == NIL)
    Lf = NIL;
  else
    Lf = GEOPART(Fp,Sf,P,Fs);

  /* Merge the two decompositions. */
  L = CCONC(Lt,Lf);

Return: /* Prepare to return. */
  return L;
}

/*
ForMulA--Cell existential query
F : a formula
C : (k-1)-level cell
P : projection factor set

Output
t : TRUE if there exists a child of C satisfying F,
    FALSE otherwise
 */
Word FMACELLEXQ(Word F,Word C,Word P)
{
  Word L,t;
  L = LELTI(C,SC_CDTV);
  for(t = FALSE; t != TRUE && L != NIL; L = RED(L))
    t = FMACELLEVAL(F,FIRST(L),P);
  return (t == TRUE);
}

/*
Stack requirements for truth invariance
 */
Word SRTI(Word C,Word P)
{
  Word L,S,a,b,c,sa,sb,i,s;
  L = PCADSCANL(C,1);
  for(S = NIL; L != NIL; L = RED(L)) {
    FIRST3(FIRST(L),&a,&b,&c);
    if (LELTI(a,SC_TMPM) != LELTI(b,SC_TMPM) ||
	LELTI(b,SC_TMPM) != LELTI(c,SC_TMPM)) {
      sa = LELTI(a,SC_SIGN);
      sb = LELTI(b,SC_SIGN);
      for(s = NIL, i = 1; sb != NIL; sa = RED(sa), sb = RED(sb), i++)
	if (FIRST(sa) != 0 && FIRST(sb) == 0)
	  s = COMP(i,s);
      s = CINV(s);
      S = COMP(s,S); } }
  return S;
}

/*
LSUNION
 */
Word LSUNION(Word L)
{
  Word U;
  if (L == NIL) return NIL;
  for(ADV(L,&U,&L); L != NIL; L = RED(L))
    U = SUNION(U,FIRST(L));
  return U;
}


/*
Is hitting set.

S : an ordered set of BETA-digits
L : a list of ordered sets of BETA-digits

*/
Word ISHITSET(Word S,Word L)
{
  Word t;
  for(t = 1; L != NIL && t; L = RED(L))
    t = (SINTER(FIRST(L),S) != NIL);
  return t;
}


/*
pretty-up the formula
 */

Word PUF(Word F, Word k)
{
  Word o1,o2,o3,o2p,t;


  t = FTYPEINFO(F);
  if ((t == ANDOP || t == OROP) && LENGTH(F) == 2)
    return PUF(SECOND(F),k);


  if (k == 0) return LIST1(TRUE);
  
  FIRST3(F,&o1,&o2,&o3);
  o2p = PUF(o2,k-1);
  if (FTYPEINFO(o2p) == TRUE) {
    if (FTYPEINFO(o3) == TRUE)
      return LIST1(TRUE);
    else
      return o3; }
  else {
    if (FTYPEINFO(o3) == TRUE)
      return o2p;
    
    if (FTYPEINFO(o2p) == ANDOP)
      return CCONC(o2p,LIST1(o3));
    else
      return LIST3(ANDOP,o2p,o3); }

}

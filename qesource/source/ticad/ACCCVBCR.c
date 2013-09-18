/*======================================================================
            T <- ACCCVBCR(k,c,B1,b;B1hOPT)

Are cell coordinates corresponding to variables in B1 constant? 
(Rational)

Inputs:
k : a level
c : a k-level cell
B1: a (k + 1)-level polynomial
b : the sample point for c
B1h: optional argument.  If non-zero, B1h is a pointer to a Word in 
     which the function will store B1 evaluated at each coordinate that
     was able to determine to be constant.

Output:
T : TRUE if ACCCVBC determines that the coordinates of c corresponding 
    to variables that appear in B1 are constant, UNDET if ACCCVBCR
    cannot be certain, FALSE if it knows there is a coordinate that is 
    not constant and that correspdonds to a variable that appears in B1.
======================================================================*/
#include "qepcad.h"
static Word SPECIALSUBSR(Word k, Word a, Word Q);
static Word SECTIONPOLS(Word k, Word c, Word P);

Word QepcadCls::ACCCVBCR(Word k, Word c, Word B1, Word b, Word* B1h)
{
  Word d, nnf, dV, IV, cp, i, I_i, d_i, c_i, L, Q, Qb, Qbs, F, Fp, a;

Step1: /* Initialization **********************************************/
  a = NIL; /* this is the pseudo-sample point we're building up *******/
  F = NIL; /* Useless now, could be usefull later. ********************/
  d = 0;   /* dimension of cell c_i. **********************************/
  nnf = 0; /* number of variables not fixed. **************************/
  dV = CINV(RED(PDEGV(k+1,B1))); /* vector of degrees of first k ******
				    variables of B1. ******************/
  IV = LELTI(c,INDX);            /* vector of indices of cell c. ******/


Step2: /* Loop over each level from 1 to k ****************************/
  c_i = GVPC;
  for(i = 1; i <= k; i++) {
    I_i = LELTI(IV,i);
    d_i = LELTI(dV,i);
    c_i = LELTI(LELTI(c_i,CHILD),I_i);
    
Step3: /* c_i is a section over a 0-dimensional cell ******************/
    if ((I_i % 2 == 0) && d == 0) {
      a = SUFFIX(a,LELTI(b,i));
      continue; }
    
Step4: /* c_i is a section over a cell of dimension greater than zero */
    if ((I_i % 2 == 0) && d > 0) {
      for(L=SECTIONPOLS(i,c_i,GVPF),Qbs=1,Fp=NIL; L != NIL; L=RED(L)) {
	Q = RPFIP(i,LELTI(FIRST(L),PO_POLY));
	Qb = SPECIALSUBSR(i,a,Q); /* Qb can't be zero, by definition of 
				     SECTIONPOLS */
	Qbs = RPEMV(nnf + 1,Qb,LELTI(b,i));
	if (Qbs == 0) {
	  a = SUFFIX(a,LELTI(b,i));
	  break; }
	else
	  Fp = COMP(Qb,Fp); }
      if (L == NIL) {
	F = CCONC(F,Fp);
	nnf++;
	a = SUFFIX(a,NIL);
      } }
    
Step5: /* c_i is a sector *********************************************/
    if (I_i % 2 == 1) {
      d++;
      nnf++;
      a = SUFFIX(a,NIL); }
  }

/*Step6: a is the psuedo-sample point, check that B1 is univariate at a. */
  bool uniq = true;
  Word B1b = SPECIALSUBSR(k+1,a,RPFIP(k+1,B1));
  for(Word B1s = B1b; uniq && B1s != 0; B1s = PRED(B1s))
    uniq = IPCONST(nnf,PLDCF(B1s));
  if (B1h != 0) *B1h = B1b;

  return uniq ? TRUE : UNDET;
}


/*======================================================================
               L <- SECTIONPOLS(k,c,P)

Inputs:
k : a level
c : a k-level cell
P : the QEPCAD data structure for the set of projection factors
    associated with the CAD in which c resides.

Outputs:
L : the list of all k-level polynomials of which c is a section.
======================================================================*/
static Word SECTIONPOLS(Word k, Word c, Word P)
{
  Word L,P_k,M,i,Mp;
  L = NIL;
  P_k = LELTI(P,k);
  M = LELTI(c,MULSUB);
  for(Mp = M; M != NIL; M = RED(M)) {
    i = FIRST(FIRST(M));
    L = COMP(LELTI(P_k,i),L); }
  return L;
}

/*======================================================================
               Qp <- SPECIALSUBSR(k,a,Q)

Special substitution - rational coordinates

k : a level
a : a list of length not more than k, each element of
    which is either a rational number or NIL
Q : an element of Q[x_1,\ldots,x_k]

Output:
Qp: If  a_i1, ..., a_it are the non-nil elements of a,
    Qp is Q evaluated at x_i1 = a_i1, ... , x_it = a_it.
======================================================================*/
static Word SPECIALSUBSR(Word k, Word a, Word Q)
{
  Word r,i,Qp,L,x;
  r = k;
  i = 1;
  Qp = Q;
  for(L = a; L != NIL; L = RED(L)) {
    x = FIRST(L);
    if (x != NIL) {
      Qp = RPEV(r,Qp,i,x);
      r--;
    }
    else
      i++;  
  }
  return Qp;
}

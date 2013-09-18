/*

ForMulA polynomial list.

Inputs:
  F : an FMA formula
  P : the projection factor set to which F refers

Output:
  Q : a list of the elements of P referenced in F.  The
      elements are given in ascending order by index, i.e.
      P_i,j < P_m,n ==> i < m or [i = m and j < n].
*/
#include "extlang.h"
#define MAXLEV 200
static int comp(Word a, Word b) { return a < b ? -1: a > b; }
static Word subprog(Word F);


Word FMAPOLLIST(Word F, Word P)
{
  Word Q,L,i,j,n,np,P_i,G;

  Q = NIL;
  L = subprog(F);
  for(L = GMSDSL(L,comp); L != NIL; L = RED(L)) {
    i = 1 + FIRST(L)/(BETA/MAXLEV);
    j = 1 + FIRST(L)%(BETA/MAXLEV);
    for(P_i = LELTI(P,i); 
	THIRD(LELTI(FIRST(P_i),PO_LABEL)) != j; 
	P_i = RED(P_i));
    Q = COMP(FIRST(P_i),Q); }

  return INV(Q);
}


static Word subprog(Word F)
{
  Word L,Fp,i,j;
  L = NIL;

  switch(FIRST(F)) {

  case ANDOP: /* AND's and OR's. */ 
  case OROP:
    for(Fp = RED(F); Fp != NIL; Fp = RED(Fp))
      L = CONC(subprog(FIRST(Fp)),L);
    break;

  case TRUE: /* Constants. */
  case FALSE: 
    break;

  case NOTOP: /* Negation. */
    L = subprog(SECOND(F));
    break;

  case RIGHTOP: /* Implications. */
  case LEFTOP:
  case EQUIOP:
    L = CONC(subprog(SECOND(F)),subprog(THIRD(F)));
    break;

  default: /* Atomic formulas. */
    FIRST2(FIRST(F),&i,&j);
    L = LIST1((BETA/MAXLEV)*(i-1) + j-1); /* Note: I assume GVNFV < MAXLEV! */
  }

return L;
}

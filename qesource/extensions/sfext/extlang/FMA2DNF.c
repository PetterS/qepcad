/*
ForMulA to disjunctive normal form.
*/
#include "extlang.h"

Word FMA2DNF(Word F)
{
  Word  F2,L,D,A,B,S;

  switch(FIRST(F)) {

  case ANDOP:
    ADV(RED(F),&F2,&L);
    A = FMA2DNF(F2);
    if (L == NIL)
      D = A;
    else {
      B = FMA2DNF(COMP(ANDOP,L));
      D = DNFPROD(A,B); }
    break;

  case OROP:
    for(D = LIST1(OROP), L = RED(F); L != NIL; L = RED(L)) {
      S = FMA2DNF(FIRST(L));
      S = RED(S);
      D = CONC(D,S); }
    break;

  default:
    D = LIST2(OROP,LIST2(ANDOP,F));
    break;
  }

  return D;
}

Word DNFPROD(Word A, Word B)
{
  Word o,a1,R,C,D,x,y,L;
  ADV2(A,&o,&a1,&R);
  if (R != NIL)
    C = RED(DNFPROD(COMP(OROP,R),B));
  else
    C = NIL;

  D = LIST1(OROP);
  for(L = RED(B); L != NIL; L = RED(L)) {
    x = FIRST(L);
    y = LIST1(CCONC(a1,RED(x)));
    D = CONC(D,y); }

  D = CONC(D,C);

  return D;
}

/*
Closest index.

c : a ESCAD cell.
L : a list of ESCAD cells -- non-empty -- all of c's level.

cp: the ESCAD cell in L with index closest to c.

*/

#include "extlang.h"

static Word comp(Word u, Word v)
{
  Word r,t,U,V,A,B,a,b;
  r = 0;
  for(t = 0, U = u, V = v; U != NIL && t == 0; U = RED(U), V = RED(V)) {
    a = FIRST(U); b = FIRST(V);
    A = absm(a);  B = absm(b);
    t = BDCOMP(A,B);
    if (!r)
      r = BDCOMP(a,b); }
  if (!t)
    t = r;
  return t;
}

Word CLOSESTINDEX(Word c, Word L)
{
  Word u,v,w,cp,q,Q;
  u = LELTI(LELTI(c,SC_REP),INDX);
  ADV(L,&cp,&Q);
  v = VECTOR_DIF(u,LELTI(LELTI(cp,SC_REP),INDX));
  while(Q != NIL) {
    ADV(Q,&q,&Q);
    w = VECTOR_DIF(u,LELTI(LELTI(q,SC_REP),INDX));
    if (comp(v,w) > 0) {
      v = w;
      cp = q; } }
  return cp;
}

Word ISCLOSEST2(Word c, Word L1, Word L2)
{
  Word c1,c2,c3;
  c1 = CLOSESTINDEX(c,L1);
  c2 = CLOSESTINDEX(c,L2);
  c3 = CLOSESTINDEX(c,LIST2(c1,c2));
  if (c3 == c1)
    return 1;
  else
    return 2;
}

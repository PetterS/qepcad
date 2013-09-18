#include "extlang.h"
#define BIGNUM 16384

Word ESCMINHITSET(Word L)
{
  Word Q,Lp,q,S,a,b,M,m,Mp;

  Q = NIL;
  for(Lp = L; Lp != NIL; Lp = RED(Lp)) {
    q = NIL;
    for(S = FIRST(Lp); S != NIL; S = RED(S)) {
      FIRST2(FIRST(S),&a,&b);
      q = COMP((BIGNUM*a + b),q); }
    Q = COMP(LBIBMS(q),Q); }
  
  M = MINHITSET(Q,-1);
  for(Mp = NIL; M != NIL; M = RED(M)) {
    m = FIRST(M);
    Mp = COMP(LIST2(m/BIGNUM,m%BIGNUM),Mp); }

  return Mp;
  
}

/*======================================================================
                      S <- LBMIPL(L,r)

Level buckets merge into polynomial list

Input
 L : a list (L_1,...,L_s), where each L_i is a list
     of polynomials of level i
 r : a positive BDigit

Output
 S : a list of all polynomials containted in L represented
     as r-variate saclib polynomials

======================================================================*/
#include "qepcad.h"

Word LBMIPL(Word L, BDigit r)
{
  Word S, s, i, L_i;
  S = NIL;
  s = LENGTH(L);
  for(i = s; i >= 1; i--)
  {
    for(L_i = CINV(LELTI(L,i)); L_i != NIL; L_i = RED(L_i))
      S = COMP(RVSPTSVSP(i,FIRST(L_i),r),S);
  }
  return S;
}

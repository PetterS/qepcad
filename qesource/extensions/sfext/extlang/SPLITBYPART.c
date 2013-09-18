/*

Split by partition.

Inputs
L : a list of length n;
P : a list (A,B), where A and B define a partition of {1,...,n}.  A and B
    are sublists of {n, n-1, ..., 1}, i.e. they are in descending order.
n : an integer.

Output
S : a list (S1,S2), where the ith element of L is in S1 if and only if 
    i is in A.

*/
#include "qepcad.h"

Word SPLITBYPART(Word L, Word P, Word n)
{
  Word S1,S2,A,i,Lp,l,S;

  S1 = NIL; S2 = NIL;
  A = FIRST(P);
  for(i = n, Lp = CINV(L); Lp != NIL && A != NIL; i--, Lp = RED(Lp)) {
    if (i == FIRST(A)) {
      A = RED(A);
      S1 = COMP(FIRST(Lp),S1); }
    else
      S2 = COMP(FIRST(Lp),S2); }

  while(Lp != NIL) {
    ADV(Lp,&l,&Lp);
    S2 = COMP(l,S2); }

  S = LIST2(S1,S2);

  return S;
}

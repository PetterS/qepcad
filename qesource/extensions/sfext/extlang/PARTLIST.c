/*

Partition list.

Input
n : an integer.

Output
L : a list of all partitions of n into 2 sets.  Order is not important, i.e.
    if one partition is (A,B) then the partition (B,A) is not considered
    distinct.  L = (l_1,l_2,...,l_k), where l_i = (A,B) and A and B are
    a partition of {1,...,n}.  The trivial partition ({1,...,n},{}) is not
    returned.  Lists of integers are always in descending order.

*/
#include "qepcad.h"     

Word OPARTLIST(Word n)
{
  Word L,Q,A,B;

  if (n == 0)
    L = LIST1(LIST2(NIL,NIL));
  else {
    L = NIL;
    for(Q = OPARTLIST(n-1); Q != NIL; Q = RED(Q)) {
      FIRST2(FIRST(Q),&A,&B);
      L = COMP2(LIST2(COMP(n,A),B),LIST2(A,COMP(n,B)),L); }
    L = CINV(L); }
  
  return L;
}

Word PARTLIST(Word n)
{
  Word L,Q,A,B;

  if (n == 1)
    L = NIL;
  else {
    L = NIL;
    for(Q = OPARTLIST(n-1); Q != NIL; Q = RED(Q)) {
      FIRST2(FIRST(Q),&A,&B);
      if (B == NIL) continue;
      L = COMP(LIST2(COMP(n,A),B),L); }
    L = CINV(L);
  }
  return L;
}


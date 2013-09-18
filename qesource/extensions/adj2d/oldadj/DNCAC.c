/*
Determine the number of cells adjacent to cell

e = (s,J,K) as returned from LLSISS
P a projection factor
I an isolating interval for the x-coordinate of the base cell.
  It is assumed that P(i1,j1) != 0, P(i2,j1) != 0, and if K = 0
  then P(i1,j2) != 0 and P(i2,j2) != 0 otherwise P(i1,k2) != 0
  and P(i2,k2) != 0.
*/
#include "oldadj.h"

Word DNCAC(Word e, Word I, Word P)
{
  Word i1,i2,J,j1,j2,K,k1,k2,P1,P2,x1,x2,L,s,Pp;

  FIRST2(I,&i1,&i2);
  FIRST3(e,&s,&J,&K);
  FIRST2(J,&j1,&j2);
  Pp = PTMV(2,P);
  P1 = IPIPP(1,IPLBREVAL(2,Pp,i1));
  P2 = IPIPP(1,IPLBREVAL(2,Pp,i2));

  x1 = LENGTH(IPRRISI(P1,LIST2(j1,j2)));
  x2 = LENGTH(IPRRISI(P2,LIST2(j1,j2)));

  if (K != 0) {
    FIRST2(K,&k1,&k2);
    x1 += LENGTH(IPRRISI(P1,LIST2(k1,k2)));
    x2 += LENGTH(IPRRISI(P2,LIST2(k1,k2)));

    if (IUPLBREVAL(P1,j2) == 0)
      x1++;
    if (IUPLBREVAL(P2,j2) == 0)
      x2++; }

  L = LIST2(x1,x2);

  return L;
}

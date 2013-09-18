/* 
A,B  is a LBRN
find largest k s.t. A/B >= s^k
*/
#include "rend.h"

Word LBRNQORD(Word A, Word B)
{
  Word a,b,i,j,t,s,k;
  FIRST2(A,&a,&i);
  FIRST2(B,&b,&j);
  t = i - j;
  s = - SECOND( SECOND( SSILRCRI(0,RNRED(a,b)) ) );
  k = s - t - 1;

  return k;
}

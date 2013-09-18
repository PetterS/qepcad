/* Integral univariate polynomial signs of polynomial on roots.

   A : primitive IUP.
   B : an IUP relatively prime to A.
   i1, i2: endpoints of a logarithmic standard interval. 
*/
#include "sac_ext.h"

Word IUPSOPOR(Word A, Word B, Word i1, Word i2)
{
     Word L,Bp,Lp,J,j1,j2,t,j,tp,s;

Step1: /* */
  L  = IPRRISI(A,LIST2(i1,i2));
  Bp = IPPGSD(1,B);
  
Step2: /* */
  Lp = NIL;
  while(L != NIL) {
    ADV(L,&J,&L);
    FIRST2(J,&j1,&j2);
    t = LBRNSIGN(IUPLBREVAL(A,j2));
    if (t != 0) {
      while(IUPVSI(Bp,LIST2(j1,j2)) != 0) {
	j = LSIM(j1,j2);
	tp = LBRNSIGN(IUPLBREVAL(A,j));
	if (tp == t)
	  j2 = j;
	else 
	  j1 = j;
      }
    }
    s = LBRNSIGN(IUPLBREVAL(B,LSIM(j1,j2)));
    Lp = COMP(LIST2(s,LIST2(j1,j2)),Lp);
  }

  return INV(Lp);
    
}

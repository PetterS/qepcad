/*
List of logarithmic standard intervals for sections in stack.
*/
#include "oldadj.h"

Word LLSISS(Word c)
{
       Word L,S,R,l1,l2,s,M,I,b,N,J,j1,j2,K,k1,k2,t,q,d,p,C,j;

  L = LLBRSPFSS(c);
  S = LELTI(c,CHILD);
  R = NIL;

  for(ADV(L,&l1,&L); L != NIL; l1 = l2) {
    ADV(L,&l2,&L);
    ADV(RED(S),&C,&S);

     s = LELTI(C,SAMPLE);
     if (LENGTH(s) == 3) { 
         FIRST3(s,&M,&I,&b);
         ANFAF(M,I,LAST(b),&N,&J); }
     else {
       J = LELTI(s,2);
       /* Problem:  Currently the left endpoint could be a root! */
       j1 = AFFRN(SECOND(J));
       if (PDEG(FIRST(s)) == 1 && AFPEMV(1,THIRD(s),FIRST(s),j1) == 0)
	 J = LIST2(SECOND(J),SECOND(J)); }
     FIRST2(J,&j1,&j2);
     j1 = RNLBRN(j1);
     j2 = RNLBRN(j2);
     K = 0;

Step1: /* */
     /* What could go wrong? What if we have a 1 point interval? */
     if (LBRNCOMP(j1,j2) == 0) {
       j = j1;
       k1 = j;
       if (j == 0) q = 1;
       else q = SECOND(j);
       d = LBRNDIF(l2,j); /* Note:  d cannot be zero. */
       p = IMAX(SECOND(d) + 1,q);
       k2 = LBRNSUM(j,LBRNFIE(1,-p));
       j2 = j;
       d = LBRNDIF(j,l1); /* Note:  d cannot be zero. */
       p = IMAX(SECOND(d) + 1,q);
       j1 = LBRNDIF(j,LBRNFIE(1,-p));
       K = LIST2(k1,k2);
       goto Step3; }

     /* What could go wrong? What if we have an interval that's too big? */
     t = -2;
     while (LBRNCOMP(j1,l1) < 0 || LBRNCOMP(l2,j2) < 0) {
       if (t == -2)
	 t = LBRNSIGN(IUPLBREVAL(N,j2));
       j = LSIM(j1,j2);
       s = LBRNSIGN(IUPLBREVAL(N,j));
       if (s == 0) { j1 = j; j2 = j; goto Step1; }
       if (s == t)
	 j2 = j;
       else
	 j1 = j; }

  Step3: /* */
     J = LIST2(j1,j2);
     s = FIRST(LELTI(C,SIGNPF));

     R = COMP(LIST3(s,J,K),R); }

  R = INV(R);
  return R;
}

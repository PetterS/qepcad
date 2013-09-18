/*======================================================================
                   P <- DELINPOL(Word k, Word A, Word M, b)

Inputs:
k : a level
A : a (k+1)-variate saclib integral polynomial
M : the integral minimal polynomial of an algebraic number $\alpha$.
b : the $k$-tuple coordinates of a sample point, such that 
    A vanishes identically on b

Output:
P : NIL or a saclib polynomial, if NIL, then the order of A is
    constant over b, otherwise P is a delineating polynomail for
    A over B.
======================================================================*/
#include "qepcad.h"

Word DELINPOL(Word k, Word A, Word M, Word b)
{
  Word Lp,t,L,P,Q,T1,T2;
  
Step1: /* Initialize */
  Lp = NIL;
  t = 0;

Step2: /* Get list of all t-order partials (where t is 
          the generic order of A over b) evaluated at b. */
  while(Lp == NIL) {
    t = t + 1;
    L = IPALLPARTIALS(k + 1,A,t,1);    
    Lp = NIL;
    for(Lp = NIL; L != NIL; L = RED(L)) {
      P = IPAFME(k + 1,M,FIRST(L),b);
      if (P != 0) {
	Lp = COMP(P,Lp); } } }

Step3: /* Find GCD of the elements of L. */
  L = Lp;
  LPBSD(L);
  ADV(L,&P,&L);
  while (L != NIL && PDEG(P) > 0) {
    ADV(L,&Q,&L);
    AFUPGC(M,P,Q,&P,&T1,&T2); }

Return: /* Return */
  if (PDEG(P) > 0)
    return P;
  else
    return NIL;
  
}

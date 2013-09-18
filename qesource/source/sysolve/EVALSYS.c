/*======================================================================
                      L <- EVALSYS(S,t,R)

Eval System at rational number 

Inputs:
  S = (S_1,...,S_r), S_i a list of i-variate saclib pols
      defining a system of equations.
  t an integer, 1 <= t <= r
  R a rational number

Outputs:
  L : a system that is equivalent to S with R substituted for x_t.
  NOTE: if Q is a polynomial in the system of positive
  degree in x_s, where s > t, then Q will be represented
  in L as an s-variate polynomial, despite the fact that
  we know a priori that "x_t" will not exist in Q.
======================================================================*/
#include "qepcad.h"

Word EVALSYS(Word S, BDigit t, Word R)
{
  Word r, L, i, S_i, Ap, a, A, is, As, F, f, ip, fp, s, c;
  
Step1: /* Construct the skelaton of L, the answer. */
  r = LENGTH(S);
  L = NIL;
  for(i = 1; i <= r; i++)
    if (i < t)
      L = COMP(LELTI(S,i),L);
    else
      L = COMP(NIL,L);
  L = CINV(L);

Step2: /* Sub R -> x_t for all levels >= t */
  for(i = t; i <= r; i++)
  {
    for(S_i = LELTI(S,i); S_i != NIL; S_i = RED(S_i))
    {
      /* Make substitution */
      Ap = IPRNEVAL(i,FIRST(S_i),t,R);
      if (Ap == 0) continue;

      IPSRP(i,Ap,&a,&A);
      PSIMREP(i,A,&is,&As);
      if (is == 0) { L = 1; goto Return; }
      SLELTI(L,is,COMP(As,LELTI(L,is)));
    }
  }

Return: /* Prepare to return */
  return L;
}

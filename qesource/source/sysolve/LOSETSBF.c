/*======================================================================
                      L <- LOSETSBF(S,r)

List of (polynomial) systems equivalent to (polynomial) system by 
factorization

Inputs:
   S : a list of r-variate SACLIB polynomials (i.e. a system)
   r : a BDigit

Outputs:
   L : a list of lists of irreducible r-variate SACLIB polynomials 
       (i.e. a list of systems).  The union of systems in L is 
       equivalent to S, and is constructed by factoring the elements of
       S into irreducibles.
======================================================================*/
#include "qepcad.h"

Word LOSETSBF(Word S, BDigit r)
{
  Word L, f, Sp, Lp, s, c, F, g, Ls;

Step1: /* Base case, S empty */
  if (S == NIL)
  {
    L = LIST1(NIL);
    goto Return;
  }

Step2: /* Factor first elements and get system for rest */
  ADV(S,&f,&Sp);
  Lp = LOSETSBF(Sp,r);
  IPFAC(r,f,&s,&c,&F);

Step3: /* Each factor and each rest-system produce a new system */
  L = NIL;
  while(F != NIL) {
    ADV(F,&g,&F); 
    for(Ls = Lp; Ls != NIL; Ls = RED(Ls))
      L = COMP(COMP(SECOND(g),FIRST(Ls)),L);
  }

Return: /* Prepare to return */
  return L;
}
  

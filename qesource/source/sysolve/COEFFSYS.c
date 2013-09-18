/*======================================================================
                           S <- COEFSYS(r,A)
Coefficient systems

Inputs
  r : the level
  A : an r-variate saclib polynomial

Outputs
  S : a list S = (S_1,S_2,...,S_k) where each S_i is a list of 
      primitive irreducible (r-1)-variate saclib polynomials.  A is 
      nulllified exactly at the union of solutions of each system S_i.
======================================================================*/
#include "qepcad.h"

Word COEFSYS(BDigit r, Word A)
{
  Word S, C, rp, Cp, Sp,Spp, s, c, L, e, f;

Step1: /* The zero polynomial */
  if (A == 0) { S = LIST1(NIL); goto Return; }

Step2: /* Leading coefficient is constant */
  C = PLDCF(A);
  PSIMREP(r-1,C,&rp,&Cp);
  if (rp == 0)  { S = 1;  goto Return; }

Step3: /* Construct systems for reductum A */
  Sp = COEFSYS(r,PRED(A));
  if (Sp == 1) { S = 1;  goto Return; }

Step4: /* each factor of C gives a different system */
  IPFAC(r-1,C,&s,&c,&L);
  S = NIL;
  while (L != NIL)
  {
    FIRST2(FIRST(L),&e,&f);
    L = RED(L);
    for(Spp = Sp; Spp != NIL; Spp = RED(Spp))
    {
      s = COMP(f,FIRST(Spp));
      S = COMP(s,S);
    }
  }

Return: /* Prepare to return */
  return S;
}


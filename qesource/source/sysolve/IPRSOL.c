/*======================================================================
                      R <- IPRSOL(r,P)

Integral polynomial rational solution

Inputs
  P : a primitive irreducible integral r-variate SACLIB polynomial
Output
  R : which is NIL unles P = D x_r + N, where D,N are integers, then 
      R is the rational number satisfying P(R) = 0.


======================================================================*/
#include "qepcad.h"

Word IPRSOL(BDigit r, Word P)
{
  Word e1,e0,c1,c0,r1,r0,P1,P0,N,D,R;

Step1: /* Quick tests */
  if (PDEG(P) != 1)
    return NIL;
  if (LENGTH(P) == 2)
    return 0;

Step2: /* Determine if P has the proper form */
  FIRST4(P,&e1,&c1,&e0,&c0);
  PSIMREP(r-1,c1,&r1,&P1);
  PSIMREP(r-1,c0,&r0,&P0);
  if (r1 != 0 || r0 != 0)
    return NIL;

Step3: /* Construct rational number solution */
  D = PLBCF(r,P);
  N = INEG(PTBCF(r,P));
  R = RNRED(N,D);

Return: /* Prepare to return */
  return R;
}

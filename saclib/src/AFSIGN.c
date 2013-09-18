/*======================================================================
                      s <- AFSIGN(M,I,a)

Algebraic number field sign.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.  
  I : an acceptable isolating interval for alpha.
  a : in Q(alpha).

Outputs
  s : a BETA-digit, s = sign(a).
======================================================================*/
#include "saclib.h"

Word AFSIGN(M,I,a)
       Word M,I,a;
{
       Word A,Is,r,s,sp;
       /* hide s,sp; */

Step1: /* a rational. */
       if (a == 0)
         {
         s = 0;
         goto Return;
         }
       FIRST2(a,&r,&A);
       s = RNSIGN(r);
       if (PDEG(A) == 0)
         goto Return;

Step2: /* Compute sign of A(alpha). */
       sp = AMSIGN(M,I,A);
       s = s * sp;

Return: /* Prepare for return. */
       return(s);
}

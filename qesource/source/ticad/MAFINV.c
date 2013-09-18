/*==========================================================================
                    b <- MAFINV(p,M,a)

Modular algebraic field element inverse.

Input
  p : a BETA-digit, p a prime.
  M : in Z/(p)[x], deg(M) > 0.
  a : in Z/(p)[x]/(M).


Output
  b : in Z/(p)[x].  If a is invertible in Z/(p)[x]/(M) then b = a^(-1).
      Otherwise, b = NIL.
==========================================================================*/
#include "qepcad.h"

Word MAFINV(Word p, Word M, Word a)
{
       Word b,r,rp;

Step1: /* deg(a) == 0. */
       if (PDEG(a) == 0) {
	 b = PMON(MDINV(p,PLDCF(a)),0);
	 goto Return;
       }

Step2: /* Compute resultant and cofactor. */
       MUPRC(p,M,a,&b,&r);

Step3: /* r = 0 ? */
       if (r == 0) {
	 b = NIL;
	 goto Return;
       }

Step4: /* Divide cofactor by resultant. */
       rp = MDINV(p,r);
       b = MPMDP(1,p,rp,b);

Return: /* Prepare for return. */
       return(b);
}

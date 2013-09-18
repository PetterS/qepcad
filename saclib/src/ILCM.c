/*===========================================================================
			       C <- ILCM(A,B)

Integer least common multiple.  

Inputs
  A,B : in Z.

Outputs
  C : lcm(A,B), C >= 0.
===========================================================================*/
#include "saclib.h"

Word ILCM(A,B)
       Word A,B;
{
       Word Ap,App,Bp,C,Cp;

Step1: /* A or B = 0. */
       Ap = IABSF(A);
       Bp = IABSF(B);
       if (Ap == 0) {
	  C = Bp;
	  goto Return; }
       else
	  if (Bp == 0) {
	     C = Ap;
	     goto Return; }

Step2: /* A and B nonzero. */
       Cp = IGCD(Ap,Bp);
       App = IEQ(Ap,Cp);
       C = IPROD(App,Bp);

Return: /* Prepare for return. */
       return(C);
}

/*===========================================================================
			 r <- IUPENF(A)

Integral univariate polynomial, estimate number of factors.

Inputs
  A : in Z[x], deg(A) > 0.

Output
  r : a BETA-digit > 1.  r is an estimate of the number of
      integral factors of A.
===========================================================================*/
#include "saclib.h"
#define NPENF 25 /* number of primes for estimation */

Word IUPENF(A)
       Word A;
{
       Word *Ap,P,a,i,k,p,r,rp;

Step1: /* Initialize. */
       P = RED(SPRIME);
       a = PLDCF(A);
       k = 1;
       r = 0;
       rp = 0;

Step2: /* Count the number of linear factors by evaluation. */
       while (k <= NPENF) {
	  do {
	     if (P == NIL)
		FAIL("IUPENF","Prime list exhausted");
	     ADV(P,&p,&P); }
	  while (MDHOM(p,a) == 0);
	  Ap = MAPFMUP(MPHOM(1,p,A));
	  for (i = 0; i < p; i++) {
	     if (MMAPEVAL(p,Ap,i) == 0) {
		MMAPDEFL(p,Ap,i);
		if (MMAPEVAL(p,Ap,i) == 0) {
		   MAPFREE(Ap);
		   goto Step2; }
		else
		   rp++; } }
	  k++;
	  MAPFREE(Ap); }

Step3: /* Round to nearest integer. */
       r = RNROUND(RNRED(rp,NPENF));
       if ( r < 2 )
	  r = 2;

Return: /* Prepare for return. */
       return(r);
}

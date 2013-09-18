/*===========================================================================
		      L <- NORMFAC(M,A,N)

Norm polynomial factorization.

Inputs
  M : in Z[t], the minimal polynomial of an algebraic number alpha.
  A : in Q(alpha)[x].  The norm of A is squarefree, and deg(A) >= 2.
  N : in Z[x], the norm of A.

Outputs
  L : a list (N_1,...,N_r) of the positive irreducible factors of N.
===========================================================================*/
#include "saclib.h"

Word NORMFAC(M,A,N)
       Word M,A,N;
{
       Word C,F,G,L,p;

Step1: /* Compute modular factorization. */
       NORMMF(M,A,N,&p,&F,&C,&G);
       if (p == 0) {
	  L = LIST1(N);
	  goto Return; }

Step2: /* Hensel lifting with early factor detection. */
       L = NORMHLEFD(N,PDEG(M),p,F,C,G);

Return: /* Prepare for return. */
       return(L);
}

/*===========================================================================
			 L <- IUSFPF(A)

Integral univariate squarefree polynomial factorization.

Inputs
  A : in Z[x], A squarefree, positive, primitive, and of positive degree.

Outputs
  L : a list (a_1,...,a_k), with a_i in Z[X], of the positive, irreducible
      factors of A.
===========================================================================*/
#include "saclib.h"

Word IUSFPF(A)
       Word A;
{
       Word C,F,G,L,p;

Step1: /* Degree 1. */
       if (PDEG(A) == 1) { 
	  L = LIST1(A);
	  goto Return; }

Step2: /* Degree 2. */
       if (PDEG(A) == 2) { 
	  L = IUSFPF2(A); 
	  goto Return; }

Step3: /* Compute modular factorization. */
       IUSFPMF(A,&p,&F,&C,&G);
       if (p == 0) {
	  L = LIST1(A);
	  goto Return; }

Step5: /* Apply binary lifting with early factor detection. */
       L = IUPHLEFD(p,F,A,C,G);

Return: /* Prepare for return. */
       return(L);
}

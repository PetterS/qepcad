/*===========================================================================
		       B <- MMAPBM(p,A)

Medium modulus array polynomial Berlekamp matrix.

Inputs
  p : a medium prime.
  A : in Z/(p)[x], deg(A) = n >= 2, monic and squarefree.
      A is in array representation.

Output
B : an n x n array which contains the coefficients of x^{i*p} modulo A(x)
    in row i, with the coefficient of x^j in column j.
===========================================================================*/
#include "saclib.h"

Word **MMAPBM(p,A)
       Word p,*A;
{
       Word n,**B,i,*C,*D,*E;
       
Step1: /* Get array for matrix. */
       n = MAPDEG(A);
       B = GETMATRIX(n,n);

Step2: /* Compute row 0. */
       MATELT(B,0,0) = 1;
       for (i = 1; i < n; i++)
	  MATELT(B,0,i) = 0;
       
Step3: /* Compute row 1. */
       E = MMAPEXP(p,A,p); 
       MRFMAP(E,n,B,1);

Step4: /* n = 2? */
       if (n == 2) { 
	  MAPFREE(E); 
	  goto Return; }

Step5: /* Get workspace arrays. */
       C = MAPGET(2 * (n - 1));
       D = MAPGET(2 * (n - 1));

Step6: /* Compute row 2. */
       MMAPPROD(p,E,E,C); 
       MMAPREM(p,C,A); 
       MRFMAP(C,n,B,2);

Step7: /* Compute remaining rows. */
       for (i = 3; i < n; i++)
	  if (ODD(i)) { 
	     MMAPPROD(p,C,E,D); 
	     MMAPREM(p,D,A);
	     MRFMAP(D,n,B,i); }
	  else { 
	     MMAPPROD(p,D,E,C); 
	     MMAPREM(p,C,A);
	     MRFMAP(C,n,B,i); }

Step8: /* Free arrays. */
       MAPFREE(C); 
       MAPFREE(D); 
       MAPFREE(E);

Return: /* Prepare for return. */
       return(B);
}

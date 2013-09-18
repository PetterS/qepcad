/*=====================================================================
                          F <- MPFFDP(p,n)

Medium prime finite field defining polynomial.

Inputs
   p : a prime, p^2 < beta.
   n : a beta-digit, n >= 2.

Output
   F : a monic irreducible polynomial of degree n over Z_p
       having a minimal number of nonzero terms.
=======================================================================*/
#include "saclib.h"

Word MPFFDP(p,n)
	BDigit p,n;
{
	BDigit a,i,j,k,t,u;
	BDigit *A,*B;
	Word F;

Step1: /* Search for an irreducible binomial. */
	for (a = 1; a <p; a++) {
           F = LIST4(n,1,0,a);
           if (MMUPIT(p,F))
              goto Return; }

Step2: /* Search for an irreducible polynomial with three or more terms. */
	for (k = 1; k < n; k++) {
	   if (p == 2 && EVEN(k))
	      k = k + 1;
	   A = GETARRAY(k);
	   for (i = 0; i < k; i++) 
	      A[i] = i + 1;
	   do {
	      B = GETARRAY(k);
	      for (i = 0; i < k; i++)
	         B[i] = 0;
	      do {
	         F = LIST2(0,B[0] + 1);
	         for (j = 0; j < k; j++)
	            F = COMP2(A[j],B[j]+1,F);
	         F = COMP2(n,1,F);
	         if (MMUPIT(p,F))
	            goto Return;
	         t = LEXNEXT(k,p-2,B); }
	      while (t == 1);
	      FREEARRAY(B);
	      u = NEXTSS(n-1,k,A); }
 	   while (u == 1);
	   FREEARRAY(A); }
	
Return: /* Return F. */
	return(F);
}

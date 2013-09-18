/*=========================================================================
                          L <- IUSFPF2(A)

Integral univariate squarefree polynomial factorization, degree 2.

Inputs
  A : in Z[X], positive, primitive and of degree 2.

Output
  L : a list of all the irreducible factors of A.
==========================================================================*/
#include "saclib.h"

Word IUSFPF2(A)
       Word A;
{
       Word a,b,c,D1,D2,D,ap,F1,F2,f1,f2,L,d,t;

Step1: /* Compute the discriminant D. */  
       a = PCOEFF(A,2);
       b = PCOEFF(A,1); 
       c = PCOEFF(A,0);  
       D1 = IPROD(b,b);
       D2 = IPROD(IDPR(a,-4),c);
       D = ISUM(D1,D2);

Step2: /* Is D a square? */
       if (ISIGNF(D) < 0)
	 t = 1;
       else
	 ISQRT(D,&d,&t); 
       if (t != 0) { 
	 L = LIST1(A); 
	 goto Return; }

Step3: /* D a square. */
       f1 = ISUM(b,d); 
       ap = IDPR(a,2);
       F1 = IPSUM(1,PMON(ap,1),PMON(f1,0));
       F1 = IPPP(1,F1); 
       f2 = IDIF(b,d);
       F2 = IPSUM(1,PMON(ap,1),PMON(f2,0));
       F2 = IPPP(1,F2); 
       L = LIST2(F1,F2);

Return: /* Prepare for return. */
       return(L);
}

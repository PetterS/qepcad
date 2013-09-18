/*===========================================================================
			    C <- AFPPR(r,M,A,B)

Algebraic number field polynomial product.  

Inputs
    r : a BETA-digit, r >= 0.
    M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A,B : in Q(alpha)[X1,...,Xr].

Outputs
    C : in Q(alpha)[X1,...,Xr], C = A * B.
===========================================================================*/
#include "saclib.h"

Word AFPPR(r,M,A,B)
       Word r,M,A,B;
{
       Word Ap,As,Bs,C,C1,a,b,c,e,f,rp;

Step1: /* A or B zero. */
       if (A == 0 || B == 0) {
	  C = 0;
	  goto Return; }

Step2: /* r = 0. */
       if (r == 0) {
	  C = AFPROD(M,A,B);
	  goto Return; }

Step3: /* General case. */
       As = CINV(A);
       Bs = CINV(B);
       C = 0;
       rp = r - 1;
       do {
	  ADV2(Bs,&b,&f,&Bs);
	  Ap = As;
	  C1 = NIL;
	  do {
	     ADV2(Ap,&a,&e,&Ap);
	     if (rp == 0)
		c = AFPROD(M,a,b);
	     else
		c = AFPPR(rp,M,a,b);
	     C1 = COMP2(e + f,c,C1); }
	  while (Ap != NIL);
	  C = AFPSUM(r,C,C1); }
       while (Bs != NIL);

Return: /* Prepare for return. */
       return(C);
}

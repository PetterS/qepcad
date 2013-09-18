/*=========================================================================
                          L <- IPPFAC2(r,A)

Integral primitive polynomial factorization, degree 2.

Inputs
  r : a BETA-digit, r >= 1, the number of variables;
  A : in Z[X1,...,Xr], positive, primitive and of degree 2.

Output
  L : a list of pairs (e_i,A_i) consisting of all the irreducible 
      factors A_i of A with their multiplicities e_i.
==========================================================================*/
#include "saclib.h"

Word IPPFAC2(r,A)
       Word r,A;
{
       Word a,b,c,D1,D2,D,rp,ap,F1,F2,f1,f2,L,d;

Step1: /* Compute the discriminant D. */  
       a = PCOEFF(A,2);
       b = PCOEFF(A,1); 
       c = PCOEFF(A,0);  
       rp = r-1;
       D1 = IPPROD(rp,b,b);
       D2 = IPPROD(rp,IPIP(rp,-4,a),c); 
       D = IPSUM(rp,D1,D2);

Step2: /* D = 0. */
       if (D == 0) { 
	 ap = IPIP(rp,2,a);
	 F1 = IPSUM(r,PMON(ap,1),PMON(b,0));
	 F1 = IPPP(r,F1); 
	 L =  LIST1(LIST2(2,F1));
	 goto Return; }

Step3: /* Is D a square? */
       d = IPSQRT(rp,D); 
       if (d == NIL) { 
	 L = LIST1(LIST2(1,A)); 
	 goto Return; }

Step4: /* D a square. */
       f1 = IPSUM(rp,b,d); 
       ap = IPIP(rp,2,a);
       F1 = IPSUM(r,PMON(ap,1),PMON(f1,0));
       F1 = IPPP(r,F1); 
       f2 = IPDIF(rp,b,d); 
       F2 = IPSUM(1,PMON(ap,1),PMON(f2,0));
       F2 = IPPP(r,F2); 
       L = LIST2(LIST2(1,F1),LIST2(1,F2));

Return: /* Prepare for return. */
       return(L);
}

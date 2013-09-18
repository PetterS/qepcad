/*======================================================================
                      C <- MPRESDB(r,p,A,B,D)

Modular polynomial resultant, degree bounds.

Inputs
   r : a BETA-digit, r > 0.
   p : a BETA-digit, prime.
 A,B : in Z/(p)[X1,...,Xr], A and B are of positive degree.
   D : D = (d_1,...,d_{r-1}), where d_i is an upper bound for the
       degree of res(A,B) in x_i.

Outputs
  C  : in Z/(p)[X1,...,X_{r-1}], the resultant of A and B, res(A,B).
======================================================================*/
#include "saclib.h"

Word MPRESDB(r,p,A,B,D)
	BDigit r,p;
        Word A,B,D;
{
        Word As,Bs,C,Cs,Dp,E,Ep,b,L,P;
	BDigit d,i,k,**M,m,n,q,rp;

	Word T;

Step1: /* r = 1. */
        if (r == 1) {
           C = MUPRES(p,A,B);
           goto Return; }

Step2: /* Initialize. */
	m = PDEG(A);
	n = PDEG(B);
        rp = r - 1;
        C = 0;
        E = LIST2(0,1);
        i = 0;
	d = FIRST(D);
	Dp = RED(D);

Step3: /* Recursion. */
        while (i < p) {
           As = MPEVAL(r,p,A,1,i);
           if (PDEG(As) == m) {
              Bs = MPEVAL(r,p,B,1,i);
              if (PDEG(Bs) == n) {
                 Cs = MPRESDB(rp,p,As,Bs,Dp);
                 b = MPEMV(1,p,E,i);
                 b = MDINV(p,b);
                 C = MPINT(p,E,i,b,rp,C,Cs);
                 Ep = LIST4(1,1,0,p - i);
                 E = MPPROD(1,p,E,Ep);
                 if (PDEG(E) > d)
                    goto Return; } }
           i++; }

Step4: /* Algorithm fails. */
       FAIL("MPRESDB","Fails",r,p,A,B,D);

Return: /* Prepare for return. */
       return(C);
}

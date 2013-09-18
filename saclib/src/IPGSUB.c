/*===========================================================================
			    C <- IPGSUB(r,A,s,L)

Integral polynomial general substitution.

Inputs
   r : a BETA-digit, r >= 1, the number of variables.
   A : in Z[x_1,...,x_r].
   s : a BETA-digit, s >= 1.
   L : a list (B_1,...,B_r), with B_i in Z[y_1,...,y_s].

Outputs
   C  : in Z[y_1,...,y_s], C(y_1,...,y_s) =
        A(B_1(y_1,...,y_s),...,B_r(y_1,...,y_s)).
===========================================================================*/
#include "saclib.h"

Word IPGSUB(r,A,s,L)
       Word r,A,s,L;
{
       Word B,C,Lp,t;

Step1: /* A = 0. */
       if (A == 0) {
	  C = 0;
	  goto Return; }

Step2: /* A /= 0. */
       C = PINV(r,A,s);
       Lp = L;
       t = r + s;
       do {
	  ADV(Lp,&B,&Lp);
	  C = IPSUB(t,C,s+1,B);
	  t = t - 1; }
       while (Lp != NIL);

Return: /* Return. */
       return(C);
}

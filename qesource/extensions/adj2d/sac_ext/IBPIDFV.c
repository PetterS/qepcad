/*======================================================================
                       D <- IBPIDFV(P)

Integral bivariate polynomial implicit differentiantion with respect to
first variable.

Inputs
  P : element of Z[x,y].

Outputs
  D : element of Z[x,y,y'],  D(x,y,y') = implicit derivative with 
      respect to x of P(x,y), D(x,y,y') = A(x,y) y' + B(x,y).
======================================================================*/
#include "sac_ext.h"

Word IBPIDFV(Word P)
{
       Word D,A,Pp,i,c,B,cp;

Step0: /* P = 0. */
       if (P == 0) {
	 D = 0;
	 goto Return;
       }

Step1: /* Compute A(x,y). */
       A = NIL;
       Pp = P;
       while(Pp != NIL && FIRST(Pp) != 0) {
	 ADV2(Pp,&i,&c,&Pp);
	 A = COMP2(IPIP(1,i,c),i-1,A); }
       A = INV(A);
      
Step2: /* Compute B(x,y). */
       B = NIL;
       Pp = P;
       while(Pp != NIL) {
	 ADV2(Pp,&i,&c,&Pp);
	 cp = IPDMV(1,c);
	 if (cp != 0)
	   B = COMP2(cp,i,B); }
       B = INV(B);

Step3: /* Construct D. */
       if (A == NIL)
	 if (B == NIL) D = 0;
	 else          D = LIST2(0,B);
       else
	 if (B == NIL) D = LIST2(1,A);
	 else          D = LIST4(1,A,0,B);
	
Return: /* Prepare to return. */
       return D;
}

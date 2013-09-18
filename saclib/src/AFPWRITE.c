/*===========================================================================
			     AFPWRITE(r,A,V,v)

Algebraic number field polynomial write.

Inputs
  A : in Q(alpha)[X1,...,Xr], where the coefficients of A are represented 
      as (ai,Ai) where ai is in Q and Ai is in Z[x];
  r : a BETA-digit, r >= 0, the number of variables.
  V : a variable list for A.
  v : a variable for writing the base coefficients of A.

Side effects :
  A is written in the output stream in recursive format using
  the variable list V.
===========================================================================*/
#include "saclib.h"

void AFPWRITE(r,A,V,v)
       Word r,A,V,v;
{
       Word rp,Ap,Vp,V1,e,a;

Step1: /* r = 0 */
       if (r == 0) {
	  AFWRITE(A,v);
	  goto Return; }

Step2: /* r = 1 */
       if (r == 1) {
	  V1 = FIRST(V);
	  AFUPWRITE(A,V1,v);
	  goto Return; }

Step3: /* r > 1 */
       rp = r - 1;
       Ap = A;
       Vp = CINV(V);
       ADV(Vp,&V1,&Vp);
       Vp = INV(Vp);
       CWRITE('(');
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  AFPWRITE(rp,a,Vp,v);
	  if (e > 0)
	     VWRITE(V1);
	  if (e > 1) {
	     CWRITE('^');
	     AWRITE(e); }
	  if (Ap != NIL)
	     CWRITE('+'); }
       while (Ap != NIL);
       CWRITE(')');

Return: /* Prepare for return. */
       return;
}

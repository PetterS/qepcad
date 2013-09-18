/*===========================================================================
			      IPWRITE(r,A,V)

Integral polynomial write.

Inputs
  A : in Z[x_1,...,x_r].
  r : a BETA-digit, r >= 0, the number of variables.
  V : a variable list for A.

Side effects :
  A is written in the output stream in recursive format using
  the variable list V.
===========================================================================*/
#include "saclib.h"

void IPWRITE(r,A,V)
       Word r,A,V;
{
       Word rp,Ap,Vp,v,e,a;

Step1: /* r = 0 or A = 0 */
       if (r == 0 || A == 0) {
	  IWRITE(A);
	  goto Return; }

Step2: /* r = 1 */
       if (r == 1) {
	  v = FIRST(V);
	  IUPWRITE(A,v);
	  goto Return; }

Step3: /* r > 1 */
       rp = r - 1;
       Ap = A;
       Vp = CINV(V);
       ADV(Vp,&v,&Vp);
       Vp = INV(Vp);
       CWRITE('(');
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  IPWRITE(rp,a,Vp);
	  if (e > 0)
	     VWRITE(v);
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
